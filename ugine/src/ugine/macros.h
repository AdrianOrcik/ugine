#pragma once

#define ECS_GET_COMPONENT(obj,type) (type*)obj->GetComponent<type>(); 
#define ECS_ADD_COMPONENT(obj,type) (type*)obj->AddComponent<type>();
#define ECS_ADD_COMPONENT(obj,type,...) (type*)obj->AddComponent<type>(__VA_ARGS__);