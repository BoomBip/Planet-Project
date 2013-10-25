#include "Tracker.h"
#include <iostream>


Tracker* Tracker::instance = 0;
std::vector<Particle*> Tracker::_particles;
std::vector<int> Tracker::_freeIds;

Tracker::Tracker(const Tracker& t){}
void Tracker::operator=(const Tracker& t){}
Tracker::~Tracker(){}

Tracker::Tracker(int initCap){
	_particles.reserve(initCap);
	_freeIds.reserve(initCap);
	_paused = false;
}

Tracker* Tracker::create(int initCap){
	if(!instance){
		instance = new Tracker(initCap);
		atexit(cleanup);
	}

	return instance;
}

int Tracker::addParticle(sf::Vector2f location, sf::Vector2f velocity, float mass){
	int id = getFreeId();
	if(id < 0){
		if(_particles.size() + 1 >= _particles.capacity()){
			int newCap = (2*_particles.size() > _particles.max_size())? _particles.max_size(): 2*_particles.size();
			_particles.reserve(newCap);
		}
		Particle* particle = new Particle(_particles.size(), location, velocity, mass);
		id = _particles.size();
		_particles.push_back(particle);
	} else {
		_particles[id]->refactor(location, velocity, mass);
	}

	return id;
}

int Tracker::getFreeId(){
	int id = -1;
	if(!_freeIds.empty()){
		id = _freeIds.back();
		_freeIds.pop_back();
	}

	return id;
}

void Tracker::generateProtoDisk(float mass, sf::Vector2f inputLocation){
	sf::Vector2f orgin = inputLocation;

	for (int i = 0; i < 50; i++)
	{
		float distance = std::rand() % 100;
		float heading = std::rand() % 360; //random direction

		sf::Vector2f location((cos(heading) * distance) + inputLocation.x, (sin(heading) * distance) + inputLocation.y);
		sf::Vector2f velocity(0.0f, 0.0f);
		addParticle(location, velocity, mass);
	}
}

void Tracker::freeParticle(int id){
	_particles[id]->setMark(MarkStatus::DELETED);
	_freeIds.push_back(id);
}

void Tracker::cleanup(){
	for(int i = 0; i < _particles.size(); i++){
		delete _particles[i];
	}
	_particles.clear();
}

void Tracker::update(sf::Time timeFactor, sf::RenderWindow& renderWindow){

	if(_paused)
		return;

	//update Postion
	std::vector<Particle*>::iterator i;
	std::vector<Particle*>::iterator j;

	for (i = _particles.begin(); i != _particles.end(); i++){
		if ((*i)->getMark() == MarkStatus::NOMARK){

			(*i)->update(timeFactor);

			//sub-iterator for two particles affecting each other

			for (j = _particles.begin(); j != _particles.end(); j++){
				if ((*j)->id != (*i)->id && (*j)->getMark() == MarkStatus::NOMARK){

					//gravity between two particles
					(*i)->addAcel(*j);

					//Collision detection, finds distance between particles and mark() and merge() is applid to those who are too close
					sf::Vector2f distance = (*i)->getPos() - (*j)->getPos();

					if (abs(distance.x) < ((*i)->getRadius() + (*j)->getRadius()) && (abs(distance.y) < ((*i)->getRadius() + (*j)->getRadius()))){
						float mass = (*i)->getMass() + (*j)->getMass();
						sf::Vector2f middle = 0.5f*distance + (*i)->getPos();
						addParticle(middle, ((*i)->getVel() + (*j)->getVel())*0.5f, mass);
						(*i)->setMark(MarkStatus::TOBEDELETED);
						(*j)->setMark(MarkStatus::TOBEDELETED);

					}
				}
			}
		}
	}

	for (i = _particles.begin(); i != _particles.end(); i++){
		switch((*i)->getMark()){
		case NOMARK:
			(*i)->advance();
			(*i)->draw(renderWindow);
			break;
		case TOBEDELETED:
			freeParticle((*i)->id);
			break;
		case TOBEADDED:
			(*i)->setMark(NOMARK);
			break;
		case DELETED:
			//no action
			break;
		}
	}
}
