#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

/**
 * https://www.codewars.com/kata/58e24788e24ddee28e000053/train/cpp
 */
std::unordered_map<std::string, int> assembler(const std::vector<std::string> &program);

namespace simple_assembler_interpreter {
    class Machine;

    class Instruction {
    public:
        Instruction() = default;

        virtual void execute(Machine *machine) = 0;
    };
}

using namespace simple_assembler_interpreter;

static std::vector<Instruction *> parse_program(const std::vector<std::string> &program);

class simple_assembler_interpreter::Machine {
private:
    std::unordered_map<std::string, int> registers;
    int instruction_counter = 0;
public:
    Machine() = default;

    int get(const std::string &register_name) {
        if (registers.find(register_name) == registers.end()) {
            return 0;
        }

        return registers.at(register_name);
    }

    void store(const std::string &register_name, int value) {
        registers[register_name] = value;
    }

    void jump(int instructions_count) {
        instruction_counter += instructions_count;
    }

    std::unordered_map<std::string, int> expose_registers() {
        return registers;
    }

    void execute(const std::vector<std::string> &program) {
        std::vector<Instruction *> instructions = parse_program(program);

        while (instruction_counter >= 0 && instruction_counter < instructions.size()) {
            instructions[instruction_counter]->execute(this);
            instruction_counter++;
        }
    }
};

/**
 * wrapping std::string_to_int because it may throw an exception
 * See: https://codereview.stackexchange.com/a/206758
 */
static int string_to_int(const std::string &str, int *p_value, std::size_t *pos = nullptr, int base = 10);

/**
 * https://stackoverflow.com/a/5888676/13213024
 */
static std::vector<std::string> split(const std::string &txt, char ch = ' ');

class Mov : public Instruction {
private:
    std::string x;
    std::string y;
public:
    explicit Mov(std::string x, std::string y) : x(std::move(x)), y(std::move(y)) {}

    void execute(Machine *machine) override {
        int value = 0;

        if (string_to_int(y, &value) == 0) {
            machine->store(x, value);
        } else {
            machine->store(x, machine->get(y));
        }
    }
};

class Inc : public Instruction {
private:
    std::string x;
public:
    explicit Inc(std::string x) : x(std::move(x)) {}

    void execute(Machine *machine) override {
        machine->store(x, machine->get(x) + 1);
    }
};

class Dec : public Instruction {
private:
    std::string x;
public:
    explicit Dec(std::string x) : x(std::move(x)) {}

    void execute(Machine *machine) override {
        machine->store(x, machine->get(x) - 1);
    }
};

class Jnz : public Instruction {
private:
    std::string x;
    std::string y;

public:
    explicit Jnz(std::string x, std::string y) : x(std::move(x)), y(std::move(y)) {}

    void execute(Machine *machine) override {
        int value_x = 0;

        if (string_to_int(x, &value_x) != 0) {
            value_x = machine->get(x);
        }

        if (value_x != 0) {
            int value_y = 0;

            if (string_to_int(y, &value_y) != 0) {
                value_y = machine->get(y);
            }

            machine->jump(value_y - 1);
        }
    }
};

static std::vector<Instruction *> parse_program(const std::vector<std::string> &program) {
    std::vector<Instruction *> instructions;

    for (const auto &line: program) {
        auto parts = split(line);
        auto instruction = parts[0];

        if (instruction == "mov") {
            auto x = parts[1];
            auto y = parts[2];
            instructions.push_back(new Mov(x, y));
        }

        if (instruction == "inc") {
            auto x = parts[1];
            instructions.push_back(new Inc(x));
        }

        if (instruction == "dec") {
            auto x = parts[1];
            instructions.push_back(new Dec(x));
        }

        if (instruction == "jnz") {
            auto x = parts[1];
            auto y = parts[2];
            instructions.push_back(new Jnz(x, y));
        }
    }

    return instructions;
}

std::unordered_map<std::string, int> assembler(const std::vector<std::string> &program) {
    Machine machine;
    machine.execute(program);

    return machine.expose_registers();
}

static int string_to_int(const std::string &str, int *p_value, std::size_t *pos, int base) {
    try {
        *p_value = std::stoi(str, pos, base);
        return 0;
    }

    catch (const std::invalid_argument &ia) {
        return -1;
    }

    catch (const std::out_of_range &oor) {
        return -2;
    }

    catch (const std::exception &e) {
        return -3;
    }
}

static std::vector<std::string> split(const std::string &txt, char ch) {
    std::vector<std::string> strs;

    size_t pos = txt.find(ch);
    size_t initialPos = 0;

    while (pos != std::string::npos) {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs;
}
