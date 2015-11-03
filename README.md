# ECS Framework

A templated ECS framework written in C++11.

## Getting started

First, you have to create an `Ecs::World` object. It will represent the object that contains all your systems and all your entities.  
Then, you will have to define your systems. A system must inherits from `Ecs::System::Base` and have a method `void update()`. That is the method which will be called by the `Ecs::World` object.

### System example
```cpp
class CustomSystem : public Ecs::System::Base {
  void update() {
    std::cout << "Update a custom system" << std::endl;
  }
};
```

### Components definition

Defining your components is pretty similar to the definition of systems, except that there is no mandatory member function to define. You should define it as a `struct` and you must make it inherits from `Ecs::Component::Base`.

### Component example
```cpp
struct CustomComponent : Ecs::Component::Base {
  int foo;
  std::string bar;
  CustomComponent(int _foo_ = 42, std::string const& _bar_ = "bar") : foo(_foo_), bar(_bar_) {}
};
```

### Make it work

Here is an example of a full functional commented code:
```cpp
// We define a simple system
class CustomSystem : public Ecs::System::Base {
  void update() {
    std::cout << "Update a custom system" << std::endl;
  }

  // Systems can have a constructor that take parameters
  CustomSystem(std::string const& str) {
    std::cout << std << std::endl;
  }
};

// We define a simple component
struct CustomComponent : Ecs::Component::Base {
  int foo;
  std::string bar;
  CustomComponent(int _foo_ = 42, std::string const& _bar_ = "bar") : foo(_foo_), bar(_bar_) {}
};

int main(void) {
  Ecs::World w; // defining your world
  Ecs::Entity e; // defining an empty entity

  w.addSystem<CustomSystem>(1.0, "foobar"); // The first argument is the frequency of the member function update() in ms and the other arguments are directly passed to the constructor of the system

  e.addComponent<CustomComponent>(1337, "foo"); // the component is simply added to the entity
  if (e.hasComponent<CustomComponent>()) // checking if the component is contained in the entity
    e.removeComponent<CustomComponent>(); // we can remove it as simply as we are adding it
  e.addComponent<CustomComponent>(1337, "foo");
  std::cout << e.getComponent<CustomComponent>()->foo << std::endl; // getComponent() returns a pointer to the wanted component.

  w.run(); // The world is now calling all your systems until you call the w.stop() method somewhere.
  return 0;
}
```

### Exceptions

Some exceptions may be throwed by the ECS, they are all inherited from Ecs::Exception::Base which inherits from std::exception. So, the following will work:
```cpp
try {
  e.removeComponent<CustomComponent>();
  e.getComponent<CustomComponent>();
} catch (std::exception const& e) {
  std::cerr << e.what() << std::endl;
}
```

## Author

Emeraude
