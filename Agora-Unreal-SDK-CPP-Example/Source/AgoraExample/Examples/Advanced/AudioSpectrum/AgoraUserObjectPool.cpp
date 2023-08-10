#include "AgoraUserObjectPool.h"

FAgoraUserObjectPool* FAgoraUserObjectPool::Instance = nullptr;

FAgoraUserObjectPool* FAgoraUserObjectPool::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new FAgoraUserObjectPool();
		Instance->Init();
	}
	return Instance;
}

void FAgoraUserObjectPool::ReleaseInstance(std::function<void(UObject*)>& DestroyOneObjectFunc)
{
	if (Instance != nullptr)
	{
		Instance->Release(DestroyOneObjectFunc);
		delete Instance;
		Instance = nullptr;
	}
}

UObject* FAgoraUserObjectPool::GetObject(std::function<UObject* ()>& SpawnFunc,std::function<void(UObject*)>& InitObjectFunc)
{
	UObject* Object = nullptr;
	if (InActiveObjectQueue.Dequeue(Object))
	{
		ActiveObjectQueue.Enqueue(Object);
		InitObjectFunc(Object);
		return Object;
	}
	else
	{
		for (int i = 0; i < OneTimeCreated; i++) {
			CurrentCount++;
			check(CurrentCount <= MaxLimit);
			UObject* NewObject = SpawnFunc();
			InActiveObjectQueue.Enqueue(NewObject);
		}
		UObject* OneObject = nullptr;
		InActiveObjectQueue.Dequeue(OneObject);
		InitObjectFunc(OneObject);
		ActiveObjectQueue.Enqueue(OneObject);
		return OneObject;
	}
}

void FAgoraUserObjectPool::ReturnAllObject(std::function<void(UObject*)>& DeSpawnFunc)
{
	while (!ActiveObjectQueue.IsEmpty())
	{
		UObject* OneObject = nullptr;
		ActiveObjectQueue.Dequeue(OneObject);
		DeSpawnFunc(OneObject);
		InActiveObjectQueue.Enqueue(OneObject);
	}
}

void FAgoraUserObjectPool::Init()
{
	MaxLimit = 300;
	CurrentCount = 0;
	OneTimeCreated = 256;
}

void FAgoraUserObjectPool::Release(std::function<void(UObject*)>& DestroyOneObjectFunc)
{
	UObject* OneObject = nullptr;
	while (InActiveObjectQueue.Dequeue(OneObject))
	{
		DestroyOneObjectFunc(OneObject);
	}
	OneObject = nullptr;
	while (ActiveObjectQueue.Dequeue(OneObject))
	{
		DestroyOneObjectFunc(OneObject);
	}
	InActiveObjectQueue.Empty();
	ActiveObjectQueue.Empty();
}

