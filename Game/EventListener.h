#pragma once

#include <type_traits>
#include <memory>
#include <set>
#include <functional>
#include <SFML/Graphics.hpp>

template <
	typename T
>
class EventListener {
    public:
		typedef std::function<void(std::shared_ptr<T>)> CallFunction;
		typedef std::shared_ptr<CallFunction> SharedPtrFunction;

        EventListener() {
			m_Listeners = std::make_shared<std::set<WeakPtrFunction, std::owner_less<WeakPtrFunction>>>();
			m_ListenersMutex = std::make_unique<sf::Mutex>();
		}

        ~EventListener() {

		}

        SharedPtrFunction Then(CallFunction listener) {
			// insert listener into a set
			SharedPtrFunction listenerSharedPtr = std::make_shared<CallFunction>(listener);
			Then(listenerSharedPtr);

			return listenerSharedPtr;
		}

		void Then(SharedPtrFunction listener) {
			// insert listener into a set
			// Add/Remove listeners will apply in next tick
			sf::Lock Lock(*m_ListenersMutex);

			if (m_NextListeners == nullptr) {
				m_NextListeners = CopyListeners();
			}
			m_NextListeners->insert(listener);
		}

		void Remove(SharedPtrFunction listener) {
			// Add/Remove listeners will apply in next tick
			sf::Lock Lock(*m_ListenersMutex);

			if (m_NextListeners == nullptr) {
				m_NextListeners = CopyListeners();
			}
			m_NextListeners->erase(listener);
		}

        void Emit(std::shared_ptr<T> eventArg) {
			// REMEMBER: This program does not made to use in multithread enviroment.
			//           This may break a program if accessing the object the same time.

			std::set<WeakPtrFunction, std::owner_less<WeakPtrFunction>> deleteListener;

			for (WeakPtrFunction weakPtr : *m_Listeners) {
				SharedPtrFunction listener = weakPtr.lock();
				if (listener && *listener) {
					// run the listener
					(*listener)(eventArg);
				}
				else {
					// This mean all the owner of this listener does not hold this listener anymore.
					deleteListener.insert(weakPtr);
				}
			}

			// Remove unused listener
			for (WeakPtrFunction listenerWeakPtr : deleteListener) {
				sf::Lock Lock(*m_ListenersMutex);
				if (m_NextListeners != nullptr) {
					m_NextListeners->erase(listenerWeakPtr);
				}
				else {
					m_Listeners->erase(listenerWeakPtr);
				}
			}
		}

		void Tick() {
			sf::Lock Lock(*m_ListenersMutex);
			if (m_NextListeners != nullptr) {
				m_Listeners = m_NextListeners;
				m_NextListeners = nullptr;
			}
		}

		EventListener<T>& operator+=(const SharedPtrFunction& listener) {
			Then(listener);
			return *this;
		}

		EventListener<T>& operator-=(const SharedPtrFunction& listener) {
			Remove(listener);
			return *this;
		}

	private:
		typedef std::weak_ptr<CallFunction> WeakPtrFunction;

		std::shared_ptr<std::set<WeakPtrFunction, std::owner_less<WeakPtrFunction>>> CopyListeners() {
			return std::make_shared<std::set<WeakPtrFunction, std::owner_less<WeakPtrFunction>>>(*m_Listeners);
		}
		
		std::shared_ptr<std::set<WeakPtrFunction, std::owner_less<WeakPtrFunction>>> m_Listeners = nullptr;
		std::shared_ptr<std::set<WeakPtrFunction, std::owner_less<WeakPtrFunction>>> m_NextListeners = nullptr;
		std::unique_ptr<sf::Mutex> m_ListenersMutex;
};
