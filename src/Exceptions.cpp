#include "Exceptions.hpp"

Ecs::Exception::Base::Base(std::string const& str, std::string const& type, std::string const& file, std::string const& function, int line) :
  std::exception(), _str(str), _type(type), _file(file), _function(function), _line(line) {}

Ecs::Exception::Base::~Base() throw() {}

const char *Ecs::Exception::Base::what() const throw() {
  std::ostringstream oss;
  oss << _type << " error : \"" << _str << "\" in " << _function <<  " at " << _file << ":" << _line;
  return oss.str().c_str();
}

Ecs::Exception::Component::Component(std::string const& str, std::string const& file, std::string const& function, int line) :
  Ecs::Exception::Base(str, "Component", file, function, line) {}

Ecs::Exception::Entity::Entity(std::string const& str, std::string const& file, std::string const& function, int line) :
  Ecs::Exception::Base(str, "Entity", file, function, line) {}

Ecs::Exception::World::World(std::string const& str, std::string const& file, std::string const& function, int line) :
  Ecs::Exception::Base(str, "World", file, function, line) {}
