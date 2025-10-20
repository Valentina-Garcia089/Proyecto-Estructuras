# Comando para windows:
# g++ -Wall -g -std=c++17 test_menu.cpp menu/menu_commands.cpp SecuenciaGenetica/base.cpp SecuenciaGenetica/secuencia_genetica.cpp arbolCodificacion/arbolCodificacion.cpp arbolCodificacion/nodoCodificacion.cpp -o programa
CC = g++
CXXFLAGS = -Wall -g -std=c++17
CPPFLAGS = -I.

SRCS = test_menu.cpp menu/menu_commands.cpp Sistema/sistema.cpp SecuenciaGenetica/base.cpp SecuenciaGenetica/secuencia_genetica.cpp arbolCodificacion/arbolCodificacion.cpp arbolCodificacion/nodoCodificacion.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = programa

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)