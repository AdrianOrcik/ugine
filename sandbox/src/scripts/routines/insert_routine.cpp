#include "insert_routine.h"

InsertRoutine::InsertRoutine(int insertPosition, int originPosition, std::vector<SortingElement*> Elements, float speed)
	: originPosition_(originPosition), insertPosition_(insertPosition), elements_(Elements), speed_(speed)
{
	origin = elements_[originPosition_]->GetTransform()->GetLocalPosition();
	insert = elements_[insertPosition_]->GetTransform()->GetLocalPosition();

	for (int i = insertPosition_; i < originPosition_; i++)
	{
		positions.push_back(std::make_pair(elements_[i]->GetTransform()->GetLocalPosition().x,
			elements_[i + 1]->GetTransform()->GetLocalPosition().x));
	}
}

InsertRoutine::~InsertRoutine()
{
	LOG_INFO("Routine Delete");
}

//todo: define as utility (math)
float InsertRoutine::GetInterpolation2(float a, float b, float t)
{
	return a + (b - a) * t;
}

bool InsertRoutine::HasMore()
{
	//todo: define constants 
	bool hasTime = currentTime_ < 1.0f;
	if (!hasTime)
		OnCompleted();
	return hasTime;
}

void InsertRoutine::Next(float Timestep)
{
	currentTime_ += Timestep * speed_;

	//todo: (math) define as maximum and minimum
	float value = currentTime_ > 1.0f ? 1.0f : currentTime_;
	LOG_INFO("Value: {0}", value);
	int positionIndex = 0;
	for (int i = insertPosition_; i < elements_.size(); i++)
	{
		if(positionIndex <= positions.size()-1)
		{
			float x = GetInterpolation2(positions[positionIndex].first,positions[positionIndex].second, value);
			elements_[i]->GetTransform()->SetLocalX(x);
			positionIndex++;
		}		
	}

	float x = GetInterpolation2(origin.x,insert.x, value);
	elements_[originPosition_]->GetTransform()->SetLocalX(x);
}

void InsertRoutine::OnCompleted()
{
	onCompleted();
	onCompleted = NULL;
	delete this;
}
