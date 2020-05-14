#pragma once
#include <map>
#include <string>
#include <queue>

#include "ugine/ecs/entity.h"
#include "ugine/ecs/ecs.h"

namespace Ugine
{
	class ObjectPooler
	{
	public:
		ObjectPooler() 
		{

		}

		~ObjectPooler()
		{
			pool.clear();
		}

		std::map<std::string, std::queue<Entity*>> pool;

		void CreatePool(std::string poolName, Entity& entity, int amount)
		{
			std::queue<Entity*> queue;
			for (int i = 0; i < amount; i++)
			{
				Entity* gameObject = ECS::CreateCopy(entity);
				queue.push(gameObject);
			}
			pool.insert(std::make_pair(poolName, queue));
		}

		Entity* GetPooledObj(std::string poolName)
		{
			Entity* obj = pool[poolName].front();
			pool[poolName].pop();
			pool[poolName].push(obj);
			return obj;
		}
	};
}