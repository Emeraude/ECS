DIR =	src

SRCS =	$(DIR)/Component.cpp \
	$(DIR)/Entity.cpp \
	$(DIR)/Exceptions.cpp \
	$(DIR)/System.cpp \
	$(DIR)/World.cpp

OBJS =	$(SRCS:.cpp=.o)

CXXFLAGS += -Wall -Wextra -std=c++11
CXXFLAGS += -I$(DIR)

LDXXFLAGS += -shared -fPIC

TARGET = ECS.so

CXX =	g++

%.o:	%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LDXXFLAGS)

all:	$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDXXFLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(TARGET)

re:	fclean all

.PHONY:	all clean fclean re
