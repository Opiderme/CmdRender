# Noms des exécutables
TARGET = main
TEST_TARGET = test_render

# Compilateur et flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -static-libgcc -static-libstdc++

# Dossiers sources (hors fichiers contenant `main`)
SRC_DIRS = CmdRender \
           CmdRender/2dEntity \
           CmdRender/utils

# Génère la liste des fichiers source automatiquement
SRCS := $(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))

# Génère la liste des fichiers objet (.o)
OBJS := $(SRCS:.cpp=.o)

# Règle par défaut
all: $(TARGET) $(TEST_TARGET)

# Edition de liens
$(TARGET): $(OBJS) main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_TARGET): $(OBJS) test_render.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation des .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJS) main.o test_render.o $(TARGET) $(TEST_TARGET)

# Rebuild complet
re: clean all
