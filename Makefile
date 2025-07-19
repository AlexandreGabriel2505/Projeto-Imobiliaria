CXX = g++

CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

SRCS = main.cpp Corretor.cpp Imovel.cpp Cliente.cpp utils.cpp

TARGET = imobiliaria

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)