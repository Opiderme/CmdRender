# Nom de l'exécutable
TARGET = main

# Compilateur et flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -static-libgcc -static-libstdc++

# Dossiers sources
SRC_DIRS = . \
           CmdRender \
           CmdRender/2dEntity \
           CmdRender/utils

# Génère la liste des fichiers source automatiquement
SRCS := $(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))

# Génère la liste des fichiers objet (.o)
OBJS := $(SRCS:.cpp=.o)

# Règle par défaut
all: $(TARGET)

# Edition de liens
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation des .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild complet
re: clean all
