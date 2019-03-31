#include "EventManager.h"
#include "EngineAssert.h"

using namespace UrsusEngine;

//IEventHandler


void IEventHandler::AddCallback(EventFunctor& callback)
{
	//Lambda
	//What the fuck?
	auto callbackItr = std::find_if(m_Callbacks.begin(), m_Callbacks.end(), [&](const EventFunctor& foundCallback) -> bool
	{
		return callback.target<void(std::shared_ptr<IEvent>)>() == foundCallback.target<void(std::shared_ptr<IEvent>)>();
	});
	//if callback can be found, return because it's already dead inside
	if (callbackItr != m_Callbacks.end())
	{
		return;
	}
	m_Callbacks.push_back(callback);
}
void IEventHandler::RemoveCallback(EventFunctor& callback)
{
	auto callbackItr = std::find_if(m_Callbacks.begin(), m_Callbacks.end(), [&](const EventFunctor& foundCallback) -> bool
	{
		return callback.target<void(std::shared_ptr<IEvent>)>() == foundCallback.target<void(std::shared_ptr<IEvent>)>();
	});
	//if entity has not been found, return
	if (callbackItr == m_Callbacks.end())
	{
		return;
	}
	//if found then erase from vector
	m_Callbacks.erase(callbackItr);
}
void IEventHandler::Call(std::shared_ptr<IEvent> event)
{
	//copy the callbacks so that we don't have any issues when a functor is removed
	std::vector<EventFunctor> copiedCallbacks = m_Callbacks;
	//go through all of our saved callbacks and call them
	for (EventFunctor& callback : copiedCallbacks)
	{
		//std function can be called just like a normal function
		callback(event);
	}

}




EventManager::EventManager()
{

}

EventManager::~EventManager()
{
	//check if someone forgot to call RemoveEventListener
	assert(m_Listeners.empty());
}

void EventManager::AddEventListener(std::shared_ptr<IEventHandler> listener)
{
	if (std::find(m_Listeners.begin(), m_Listeners.end(), listener) != m_Listeners.end())
	{
		return;
	}
	m_Listeners.push_back(listener);
}

void EventManager::RemoveEventListener(std::shared_ptr<IEventHandler> listener)
{
	//try to get entity
	std::vector<std::shared_ptr<IEventHandler>>::iterator listenerItr = std::find(m_Listeners.begin(), m_Listeners.end(), listener);

	//if entity has not been found, return
	if (listenerItr == m_Listeners.end())
	{
		return;
	}
	//if found then erase from vector
	m_Listeners.erase(listenerItr);
}

void EventManager::PushEvent(std::shared_ptr<IEvent> event)
{
	m_Events.push(event);
}

void EventManager::Update()
{
	while (!m_Events.empty())
	{
		//get the next entry and remove it from the queue
		std::shared_ptr<IEvent> event = m_Events.back();
		m_Events.pop();

		std::vector<std::shared_ptr<IEventHandler>> copiedListeners = m_Listeners;
		for (std::shared_ptr<IEventHandler>& listener : m_Listeners)
		{
			//if the event matches to the listener
			if (listener->DoesEventMatch(event))
			{
				//call the callbacks of the listener
				listener->Call(event);
			}
		}
	}
}