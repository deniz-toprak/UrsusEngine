#pragma once
#include <memory>
#include <functional>
#include <vector>
#include <queue>

namespace UrsusEngine
{
	class IEvent
	{
	public:
		virtual ~IEvent()
		{

		}

	};

	//typedef is similiar to a define, replacing everything inside with a word
	//difference between a define is that typedefs can be used via namespaces
	typedef std::function<void(std::shared_ptr<IEvent>)> EventFunctor;

	class IEventHandler
	{
	public:
		virtual ~IEventHandler()
		{

		}

	public:
		virtual bool DoesEventMatch(std::shared_ptr<IEvent> event) = 0;
		//add callback of class which will be called when the event is thrown
		void AddCallback(EventFunctor& callback);
		//remove callback
		void RemoveCallback(EventFunctor& callback);

		//call our callbacks
		void Call(std::shared_ptr<IEvent> event);
	private:
		//conatins a list of callbacks
		std::vector<EventFunctor> m_Callbacks;
	};

	//This event manager is like me, single(ton)
	class EventManager
	{
	public:
		EventManager();
		~EventManager();

		static EventManager& GetInstance()
		{
			static EventManager _instance;

			EventManager manager;
			return _instance;
		}

		EventManager(const EventManager&) = delete; //copy constructor disabled
		EventManager& operator=(const EventManager&) = delete; //copy operator disabled

	public:
		void AddEventListener(std::shared_ptr<IEventHandler> listener);
		void RemoveEventListener(std::shared_ptr<IEventHandler> listener);

		//add event to eventmanager
		void PushEvent(std::shared_ptr<IEvent> event);
		//throw all events that have been pushed before
		void Update();


	private:
		//listeners are added, removed and updated in Update()
		std::vector<std::shared_ptr<IEventHandler>> m_Listeners;
		//events are pushed on the queue during PushEvent
		std::queue<std::shared_ptr<IEvent>> m_Events;
	};
}