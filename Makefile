all: passwords/passwords

passwords/passwords: passwords/main.cpp
	g++ passwords/main.cpp -o passwords/passwords

.PHONY: clean
clean:
	-rm passwords/passwords
