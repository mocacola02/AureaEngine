#include "Runtime.h"
#include "../World/World.h"

bool Runtime::Initialize()
{
	running_ = true;
	return running_;
}

void Runtime::Run()
{
	const double delta = time_.Tick();
	world_.Tick(delta);
}

void Runtime::Shutdown()
{
	world_.Shutdown();

	for (Object* object : GetObjects())
	{
		DeleteObject(object);
	}

	uuidManager_.Clear();

	Exit();
}

bool Runtime::IsRunning() const
{
	return running_;
}

void Runtime::SetResultString(const String& result)
{
	exitResult_ = result;
}

void Runtime::Exit()
{
	running_ = false;
}

template<typename Type>
Type* Runtime::CreateObject()
{
	if (!IsClassBasedOn<Type, Object>())
	{
		ERROR("Invalid class type provided! The class type must derive from Object! Aborting CreateObject");
		return nullptr;
	}

	Type* newObject = new Type(this);

	if (!newObject)
	{
		ERROR("New object could not be created!");
		return nullptr;
	}

	if (!LeaseUUID(newObject))
	{
		ERROR("Could not lease UUID for new object!");
		DeleteObject(newObject);
		return nullptr;
	}

	if (!newObject->Initialize())
	{
		ERROR("Failed to initialize new object!");
		DeleteObject(newObject);
		return nullptr;
	}

	return newObject;
}

void Runtime::DeleteObject(Object* object)
{
	object->Shutdown();
	GetUUIDManager().UnregisterObject(object);
	delete object;
}

Array<Object*> Runtime::GetObjects()
{
	return GetUUIDManager().GetObjects();
}

template<typename Type>
Array<Type*> Runtime::GetObjectsOfType()
{
	Array<Type*> objects;

	for (Object* object : GetUUIDManager().GetObjects())
	{
		if (object->IsOfType<Type>())
		{
			objects.Add(object);
		}
	}

	return objects;
}


template<typename Base, typename Derived>
bool Runtime::IsClassBasedOn() const noexcept
{
	Derived temp;
	return dynamic_cast<Base*>(&temp) != nullptr;
}

AudioManager& Runtime::GetAudioManager() noexcept
{
	return audioManager_;
}

ConfigManager& Runtime::GetConfigManager() noexcept
{
	return configManager_;
}

InputManager& Runtime::GetInputManager() noexcept
{
	return inputManager_;
}

NetworkManager& Runtime::GetNetworkManager() noexcept
{
	return networkManager_;
}

RenderManager& Runtime::GetRenderManager() noexcept
{
	return renderManager_;
}

ResourceManager& Runtime::GetResourceManager() noexcept
{
	return resourceManager_;
}

ScriptManager& Runtime::GetScriptManager() noexcept
{
	return scriptManager_;
}

UUIDManager& Runtime::GetUUIDManager() noexcept
{
	return uuidManager_;
}

Time& Runtime::GetTime() noexcept
{
	return time_;
}

World& Runtime::GetWorld() noexcept
{
	return world_;
}

const AudioManager& Runtime::GetAudioManager() const noexcept
{
	return audioManager_;
}

const ConfigManager& Runtime::GetConfigManager() const noexcept
{
	return configManager_;
}

const InputManager& Runtime::GetInputManager() const noexcept
{
	return inputManager_;
}

const NetworkManager& Runtime::GetNetworkManager() const noexcept
{
	return networkManager_;
}

const RenderManager& Runtime::GetRenderManager() const noexcept
{
	return renderManager_;
}

const ResourceManager& Runtime::GetResourceManager() const noexcept
{
	return resourceManager_;
}

const ScriptManager& Runtime::GetScriptManager() const noexcept
{
	return scriptManager_;
}

const UUIDManager& Runtime::GetUUIDManager() const noexcept
{
	return uuidManager_;
}

const Time& Runtime::GetTime() const noexcept
{
	return time_;
}

const World& Runtime::GetWorld() const noexcept
{
	return world_;
}