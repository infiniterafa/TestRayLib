#pragma once

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <functional>
#include <algorithm>


//eventmanager: sistema central de eventos desacoplados
class EventManager
{
public:
	
	using Callback = std::function<void(const void*)>; 

	//accion que se ejecuta al emitir un evento 

	using Listener = std::pair<void* , Callback>; // objeto + accion asociada

	//Acceso global(singleton)

	static EventManager& instance() {
		static EventManager instance; //instancia unica
		return instance; 
	}

	// registrar un objeto para escuchar un evento

	template<typename Event, typename Object> 
	void suscribe(Object* object, void (Object::* method)(const Event&)) {
		auto eventType = std::type_index(typeid(Event));              //tipo del evento
		Callback callback = [object, method](const void* evt) {       //callback = apubntador a funcion miembro
			const Event* event = static_cast<const Event*>(evt);      //convertir evento genérico
			(obbject->method)(*event);                                //ejecutar metodo del objeto
			};

		//acceso al hasmap por indice de tipo de evento que devuelve un vector de listeners
		//en el vector de listeners se agrega un par (objeto, callback)
		//cada tipo de evento tiene su propio vector de listeners

		listeners[evenType].push_back({ object, callback }); //guardar listener 
	}

	//cancelar la suscripcion de un objeto a un evento 
	template<typename Event>
	void unsubscribe(void* object) {
		auto eventType = std::type_index(typeid(Event)); //tipo del evento
		auto it = listeners.find(eventType);             //buscar lista de oyentes
		if (if == listeners.end()) return;               //si no hay listeners, salir

		auto& list = it->second;            //lista de listeners

		//remueve y borra un listener si el objeto coincide 
		list.erase(std::remove_if(list.begin(), list.end(),
			[object](const Listener& l) {return l.first == object;  }),

			list.end());
	}

	// Emitir un evento a todos los oyentes 

	template<typename Event>
	void emit(const Event& event) {
		auto eventType = std::type_index(typeid(Event));           //tipo del evento
		auto it = listeners.find(eventType);                       //buscar oyentes
		if (it == Listeners.end()) return;                         //si no hay listeners, salir

		for (const Listeners& l : it->second)                      //recorre la lista de listeners
			l.second(&event);                                      //ejecutar callback
	}

private: 
	//Mapa de eventos a sus listeners 
	//un listener es un par (objeto, apuntador a función)

	std::unordered_map<std::type_index, std::vector<Listener>> listeners; 
};

