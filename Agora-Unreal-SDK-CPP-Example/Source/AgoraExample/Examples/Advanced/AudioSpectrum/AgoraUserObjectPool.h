#pragma once
#include "CoreMinimal.h"
#include "Containers/Queue.h"
#include <functional>



class FAgoraUserObjectPool {

public:
	static FAgoraUserObjectPool* GetInstance();
	static void ReleaseInstance(std::function<void(UObject*)>& DestroyOneObjectFunc);

protected:
	static FAgoraUserObjectPool* Instance;


public:

	UObject* GetObject(std::function<UObject* ()>& SpawnFunc, std::function<void(UObject*)>& InitObjectFunc);

	void ReturnAllObject(std::function<void(UObject*)>& DeSpawnFunc);

	void Init();

	void Release(std::function<void(UObject*)>& DestroyFunc);

private:
	TQueue<UObject*> InActiveObjectQueue;
	TQueue<UObject*> ActiveObjectQueue;
	int CurrentCount = 0;
	int MaxLimit = 0;
	int OneTimeCreated = 256;
};

