#include "carObject.h"



carObject::carObject()
{
}

carObject::carObject(char * texture, glm::vec2 position, glm::vec2 finalposition, SpriteRenderer *renderer)
{
	this->texture = _strdup(texture);
	this->position = position;
	this->finalPosition = finalposition;
	Renderer = renderer;
}


void carObject::Move()
{
	if (shouldStop==false)
	{
		GetObstacle();
		if (DistanceRemain() > 10.0f)
		{
			//if (this->rotation==0.0f||this->rotation==90.0f||this->rotation)
			_position pos1, pos2;
			pos1.x = position.x;
			pos1.y = position.y;
			pos2.x = finalPosition.x;
			pos2.y = finalPosition.y;
			CalculateSpeed();
			_position rez = calculate_p(currSpeed, pos1, pos2);
			position.x = rez.x;
			position.y = rez.y;
			
		}
		else
		{
			if (pipe->size() > 0)
			{
				SuperPipeLine *buf = pipe->front();
				position = finalPosition;
				finalPosition = buf->nextPosition;
				rotation = buf->nextRotation;
				pipe->erase(pipe->begin());
			}
			else
				shouldStop = true;
		}
	}

}
void carObject::CalculateSpeed()
{
	if (currSpeed < minSpeed)
		currSpeed = minSpeed;
	if (objInFace)
	{
		double dist = sqrt((position.x - carinFace->position.x)*(position.x - carinFace->position.x) + (position.y - carinFace->position.y)*(position.y - carinFace->position.y));
		if (dist < 100.0f)
		{
			if (dist <= 50.0f)
				this->currSpeed = carinFace->currSpeed;
			else
				if (this->currSpeed > carinFace->currSpeed)
					currSpeed -= 0.05f;
			return;
		}
	}
	if (DistanceRemain() > 200.0f)
	{
		if (currSpeed < maxSpeed)
			currSpeed += 0.01f;

	}
	else
		if (currSpeed > minSpeed)
			currSpeed -= 0.01f;
}

void carObject::GetObstacle()
{
	carinFace = nullptr;
	this->objInFace = false;
	for (int i = 0;i < carListLim;i++)
	{
		if (i!=exceptedCar)
			if (this->finalPosition == carsList[i]->finalPosition&&this->rotation == carsList[i]->rotation)
			{
				std::cout << "gasit";
				this->objInFace = true;
				carinFace = carsList[i];
				break;
			}
	}
}

void carObject::Draw()
{
	if (Renderer!=nullptr)
		Renderer->DrawSprite(ResourceManager::GetTexture(this->texture), glm::vec2(position.x+2*cos(rotation), position.y + 2*sin(rotation)), glm::vec2(40, 20),rotation);
}

carObject::~carObject()
{
}

void carObject::CalculateEcuation()
{
	a = (position.y - finalPosition.y) / (position.x - finalPosition.x);
	b = position.y - a*position.x;
}

float carObject::DistanceRemain()
{
	return sqrt((position.x - finalPosition.x)*(position.x - finalPosition.x) + (position.y - finalPosition.y)*(position.y - finalPosition.y));
}

_position carObject::calculate_p(double unit, _position initial, _position final)
{
	_position move;
	double angle = atan((final.y - initial.y) / (final.x - initial.x));
	if (((initial.x <= final.x) && (initial.y <= final.y)) || ((initial.x <= final.x) && (initial.y >= final.y)))
	{
		move.x = initial.x + cos(angle)*unit;
		move.y = initial.y + sin(angle)*unit;
	}
	else
	{
		move.x = initial.x - cos(angle)*unit;
		move.y = initial.y - sin(angle)*unit;
	}
	return move;
}

