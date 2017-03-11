# ECS Framework

A portable templated Entity-Component-System framework written in C++11.  
This branch is for unstable version 2.0. For the stable version 1.0, see git tag v1.0.

## Getting started

First, you have to create an `Ecs::World` object. It will represent the object that contains all your systems and all your entities.  
Then, you will have to define your systems. A system must inherit from `Ecs::System::Base` and have a method `void update()`. That is the method which will be called by the `Ecs::World` object.

### System example
```cpp
class CustomSystem : public Ecs::System {
  void update() {
    std::cout << "Update a custom system. World has " << w.getEntities().size() << " entities." << std::endl;
  }
};
```

### Components definition

Defining your components is pretty similar to the definition of systems, except that there is no mandatory member function to define. You should define it as a `struct` and you must make it inherit from `Ecs::Component::Base`.

### Component example
```cpp
struct CustomComponent : Ecs::Component {
  int foo;
  std::string bar;
  CustomComponent(int _foo_ = 42, std::string const& _bar_ = "bar") : foo(_foo_), bar(_bar_) {}
};
```

### Make it work

Here is an example of a full functional commented code:
```cpp
// We define a simple system
class CustomSystem : public Ecs::System {
  void update(Ecs::World& w) {
    for (std::vector<Ecs::Entity *>::iterator it = w.getEntities().begin(); it != w.getEntities().end(); ++it)
      w.remove(it); // you must use this function to remove an entity. Otherwise it should be dirty.
    std::cout << "Update a custom system." << std::endl;
  }

public:
  // Systems can have a constructor that takes parameters
  CustomSystem(std::string const& str) {
    std::cout << str << std::endl;
  }
};

// We define a simple component
struct CustomComponent : Ecs::Component {
  int foo;
  std::string bar;
  CustomComponent(int _foo_ = 42, std::string const& _bar_ = "bar") : foo(_foo_), bar(_bar_) {}
};

int main(void) {
  Ecs::World w; // defining your world
  Ecs::Entity *e = new Ecs::Entity(); // defining an empty entity

  w.add<CustomSystem>("foobar"); // The arguments are forwarded to the constructor of the system

  e->add<CustomComponent>(1337, "foo"); // the component is simply added to the entity
  if (e->has<CustomComponent>()) // checking if the component is contained in the entity
    e->remove<CustomComponent>(); // we can remove it as simply as we are adding it
  e->add<CustomComponent>(1337, "foo");
  std::cout << e->get<CustomComponent>()->foo << std::endl; // get() returns a pointer to the wanted component.

  w.add(e); // the entity will be added to the world.

  w.setSleepDuration(std::chrono::milliseconds(50)); // A 50 milliseconds sleep will occur between each system update. Default value is 10ms
  w.run(); // The world is now calling all your systems until you call the w.stop() method somewhere.
  return 0;
}
```

### Exceptions

Some exceptions may be thrown by the ECS, they are all inherited from Ecs::Exception::Base which inherits from std::exception. So, the following will work:
```cpp
try {
  e->remove<CustomComponent>();
  e->get<CustomComponent>();
} catch (std::exception const& e) {
  std::cerr << e.what() << std::endl;
}
```

## Author

Emeraude
