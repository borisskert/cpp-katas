#include <string>
#include <utility>
#include <vector>
#include <iostream>

/**
 * https://www.codewars.com/kata/58678d29dbca9a68d80000d7/train/cpp
 */
std::string interpreter(const std::string &code, const std::string &tape);

class Tape {
private:
    int pointer;
    std::vector<char> content;

    explicit Tape(std::vector<char> content);

public:
    bool moveRight();

    bool moveLeft();

    void flipBit();

    bool readBit();

    bool isOutOfBounds() {
        return this->pointer < 0 || this->pointer >= this->content.size();
    }

    std::string expose();

    static Tape *from(std::string tape);
};

class Code {
private:
    int pointer;
    std::vector<char> content;

    explicit Code(std::vector<char> content);

public:
    bool jumpForward();

    bool jumpBackward();

    char readByte();

    bool next();

    bool isOutOfBounds() {
        return this->pointer < 0 || this->pointer >= this->content.size();
    }

    static Code *from(std::string string);
};

class Machine {
private:
    Tape *tape;
    Code *code;

    explicit Machine(Code *code, Tape *tape);

public:
    void run();

    bool flipBit();

    bool moveRight();

    bool moveLeft();

    bool readBit();

    bool jumpForward();

    bool jumpBackward();

    std::string exposeTape();

    ~Machine() {
        if (this->tape != nullptr)
            delete this->tape;
        if (this->code != nullptr)
            delete this->code;
    }

    static Machine from(std::string codeString, std::string tapeString);
};

class Instruction {
public:
    virtual bool execute(Machine &machine) = 0;

    static Instruction *from(char c);
};

void Machine::run() {
    while (!this->code->isOutOfBounds() && !this->tape->isOutOfBounds()) {
        char instruction = this->code->readByte();
        Instruction *i = Instruction::from(instruction);

        if (!i->execute(*this)) {
            break;
        }

        if (!this->code->next()) {
            break;
        }
    }
}

Machine Machine::from(std::string codeString, std::string tapeString) {
    Code *code = Code::from(std::move(codeString));
    Tape *tape = Tape::from(std::move(tapeString));
    return Machine(code, tape);
}

Machine::Machine(Code *code, Tape *tape) {
    this->code = code;
    this->tape = tape;
}

bool Machine::flipBit() {
    this->tape->flipBit();
    return true;
}

bool Machine::moveRight() {
    return this->tape->moveRight();
}

bool Machine::moveLeft() {
    return this->tape->moveLeft();
}

bool Machine::readBit() {
    return this->tape->readBit();
}

bool Machine::jumpForward() {
    return this->code->jumpForward();
}

bool Machine::jumpBackward() {
    return this->code->jumpBackward();
}

std::string Machine::exposeTape() {
    return this->tape->expose();
}

std::string interpreter(const std::string &code, const std::string &tape) {
    std::cout << "code: " << code << std::endl << "tape: " << tape << std::endl;

    Machine machine = Machine::from(code, tape);
    machine.run();
    return machine.exposeTape();
}

Tape *Tape::from(std::string tape) {
    std::vector<char> chars(tape.begin(), tape.end());
    return new Tape(chars);
}

Tape::Tape(std::vector<char> content) {
    this->pointer = 0;
    this->content = std::move(content);
}

bool Tape::moveRight() {
    if (this->pointer < this->content.size() - 1) {
        this->pointer++;
        return true;
    }

    return false;
}

bool Tape::moveLeft() {
    if (this->pointer > 0) {
        this->pointer--;
        return true;
    }

    return false;
}

void Tape::flipBit() {
    char newValue = this->content[this->pointer] == '0' ? '1' : '0';
    this->content[this->pointer] = newValue;
}

bool Tape::readBit() {
    return this->content[this->pointer] == '1';
}

std::string Tape::expose() {
    return {this->content.begin(), this->content.end()};
}


Code::Code(std::vector<char> content) {
    this->pointer = 0;
    this->content = std::move(content);
}

Code *Code::from(std::string string) {
    std::vector<char> chars(string.begin(), string.end());
    return new Code(chars);
}

bool Code::jumpForward() {
    int openBrackets = 0;

    this->pointer++;

    while (this->pointer < this->content.size()) {
        char current = this->content[this->pointer];

        if (current == '[') {
            openBrackets++;
        } else if (current == ']') {
            if (openBrackets == 0) {
                return true;
            }

            openBrackets--;
        }

        this->pointer++;
    }

    return false;
}

bool Code::jumpBackward() {
    int closeBrackets = 0;

    this->pointer--;

    while (this->pointer >= 0) {
        char current = this->content[this->pointer];

        if (current == ']') {
            closeBrackets++;
        } else if (current == '[') {
            if (closeBrackets == 0) {
                return true;
            }

            closeBrackets--;
        }

        this->pointer--;
    }

    return false;
}

char Code::readByte() {
    return this->content[this->pointer];
}

bool Code::next() {
    this->pointer++;
    return this->pointer >= 0 && this->pointer < this->content.size();
}

class MoveLeft : public Instruction {
public:
    bool execute(Machine &machine) override;
};

class MoveRight : public Instruction {
public:
    bool execute(Machine &machine) override;
};

class FlipBit : public Instruction {
public:
    bool execute(Machine &machine) override;
};

class JumpForward : public Instruction {
public:
    bool execute(Machine &machine) override;
};


class JumpBackward : public Instruction {
public:
    bool execute(Machine &machine) override;
};

class Noop : public Instruction {
public:
    bool execute(Machine &machine) override {
        return true;
    }
};

Instruction *Instruction::from(char c) {
    switch (c) {
        case '<':
            return new MoveLeft();
        case '>':
            return new MoveRight();
        case '*':
            return new FlipBit();
        case '[':
            return new JumpForward();
        case ']':
            return new JumpBackward();
        default:
            return new Noop();
    }
}

bool MoveLeft::execute(Machine &machine) {
    return machine.moveLeft();
}

bool MoveRight::execute(Machine &machine) {
    return machine.moveRight();
}

bool FlipBit::execute(Machine &machine) {
    return machine.flipBit();
}

bool JumpForward::execute(Machine &machine) {
    if (!machine.readBit()) {
        return machine.jumpForward();
    }

    return true;
}

bool JumpBackward::execute(Machine &machine) {
    if (machine.readBit()) {
        return machine.jumpBackward();
    }

    return true;
}
