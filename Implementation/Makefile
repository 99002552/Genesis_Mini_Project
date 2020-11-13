SRC = pushandled.c\
mainpgrm.c

PROJECT_NAME = man.out

# Output directory
BUILD = build

$(PROJECT_NAME): $(SRC)
	gcc $(SRC) -o $(PROJECT_NAME)

all: $(SRC) $(BUILD)
	gcc $(SRC)  -o $(PROJECT_NAME)

run:$(PROJECT_NAME)
	./${PROJECT_NAME}

clean:
	rm -rf $(PROJECT_NAME)
$(BUILD):
	mkdir build
