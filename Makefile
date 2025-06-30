# Nome do executável
TARGET = AndLoc1D

# Diretório com os arquivos fonte
SRC_DIR = .

# Lista de arquivos fonte
SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/WaveFunction.cpp \
       $(SRC_DIR)/Cristal.cpp \
       $(SRC_DIR)/Simulador.cpp

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra

# Arquivos objeto (substitui .cpp por .o)
OBJS = $(SRCS:.cpp=.o)

# Regra padrão
all: $(TARGET)

# Como compilar o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para arquivos .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJS) $(TARGET)
