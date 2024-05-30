#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <random>

// Configs start

const bool SHUFFLE_ANSWERS = true;

// Configs end

enum Color
{
    RED,
    GREEN,
    YELLOW,
    BLUE,
    ORANGE,
    CYAN,
    RESET,
};

std::map<Color, std::string> termColor = {
    {Color::RED, "\033[91m"},
    {Color::GREEN, "\033[92m"},
    {Color::YELLOW, "\033[93m"},
    {Color::BLUE, "\033[34m"},
    {Color::ORANGE, "\u001b[38;5;166m"},
    {Color::CYAN, "\033[36m"},
    {Color::RESET, "\033[0m"},
};

template <typename T>
void shuffleVector(std::vector<T> &v)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, v.size() - 1);
    for (int i = 0; i < v.size(); ++i)
    {
        int randIndex = dis(gen);
        T temp = v[i];
        v[i] = v[randIndex];
        v[randIndex] = temp;
    }
}

class Answer
{
public:
    std::vector<std::string> correctAnswers;
    std::vector<std::string> wrongAnswers;

    std::vector<std::string> getAnswers()
    {
        std::vector<std::string> merged;
        merged.insert(merged.end(), correctAnswers.begin(), correctAnswers.end());
        merged.insert(merged.end(), wrongAnswers.begin(), wrongAnswers.end());
        return merged;
    }

    std::vector<std::string> getShuffled()
    {
        std::vector<std::string> merged;
        merged.insert(merged.end(), correctAnswers.begin(), correctAnswers.end());
        merged.insert(merged.end(), wrongAnswers.begin(), wrongAnswers.end());
        shuffleVector(merged);
        return merged;
    }
};

enum Complexity
{
    EASY,
    MEDIUM,
    DIFFICULT,
};

struct MultipleChoiceQuiz
{
    int id;
    std::string question;
    Answer answers;
    Complexity complexity;
};

class Exam
{
private:
    std::vector<MultipleChoiceQuiz> quizzes;

    std::string to_str(int a)
    {
        return std::to_string(a);
    }

    std::vector<int> getAnswersFromUser(int answerCount, int exclusiveHighBound)
    {
        std::vector<int> result;
        for (int i = 0; i < answerCount; ++i)
        {
            int input;
            std::cout << "User Answer #" << i + 1 << ": ";
            std::cin >> input;
            if (input < 0 or input >= exclusiveHighBound or std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(32767, '\n');
                --i;
                std::cout << "Wrong index! Try again" << "\n";
                continue;
            }
            result.push_back(input);
        }
        return result;
    }

public:
    Exam(std::vector<MultipleChoiceQuiz> _quizzes)
    {
        addQuizzes(_quizzes);
    }

    void addQuizzes(std::vector<MultipleChoiceQuiz> _quizzes)
    {
        quizzes.insert(quizzes.end(), _quizzes.begin(), _quizzes.end());
        checkDuplicatedIDs();
    }

    auto getQuizzes()
    {
        return quizzes;
    }

    void checkDuplicatedIDs()
    {
        std::set<int> IDs;
        for (const auto &quiz : quizzes)
            IDs.insert(quiz.id);

        if (quizzes.size() != IDs.size())
        {
            std::cout << "Error : Check your quizzes IDs!" << "\n";
            for (const auto &quiz : quizzes)
                std::cout << quiz.id << "   ";
            exit(1);
        }
    }

    void debug(bool printable)
    {
        std::string log = "";
        for (const auto &quiz : quizzes)
        {
            // id
            log += std::string("id : " + to_str(quiz.id) + "\n");

            // complexity
            switch (quiz.complexity)
            {
            case Complexity::EASY:
                log += std::string("Complexity : Easy\n");
                break;
            case Complexity::MEDIUM:
                log += std::string("Complexity : Medium\n");
                break;
            case Complexity::DIFFICULT:
                log += std::string("Complexity : Difficult\n");
                break;
            default:
                std::cerr << "The Complexity:: is not set";
                exit(1);
            }
            // question
            log += std::string("question : " + quiz.question + "\n");

            // answers
            for (int i = 0; i < quiz.answers.correctAnswers.size(); ++i)
                log += std::string("correct answer #" + to_str(i) + " " + quiz.answers.correctAnswers[i] + "\n");
            for (int i = 0; i < quiz.answers.wrongAnswers.size(); ++i)
                log += std::string("wrong answer #" + to_str(i) + " " + quiz.answers.wrongAnswers[i] + "\n");
            log += std::string("\n");
        }
        if (printable)
            std::cout << log;
    }

    void conduct()
    {
        // std::cout << "Conducting exam..." << "\n";
        while (true)
        {
            for (auto &quiz : quizzes)
            {
                std::cout << termColor[Color::BLUE] << "id: " << quiz.id << ") " << quiz.question << "    " << termColor[Color::CYAN];
                switch (quiz.complexity)
                {
                case Complexity::EASY:
                    std::cout << "Complexity : Easy\n";
                    break;
                case Complexity::MEDIUM:
                    std::cout << "Complexity : Medium\n";
                    break;
                case Complexity::DIFFICULT:
                    std::cout << "Complexity : Difficult\n";
                    break;
                default:
                    std::cerr << "The Complexity:: is not set";
                    exit(1);
                }

                std::vector<std::string> answers;
                if (SHUFFLE_ANSWERS)
                    answers = quiz.answers.getShuffled();
                else
                    answers = quiz.answers.getAnswers();

                std::cout << termColor[Color::RESET] << "\n";
                for (int i = 0; i < answers.size(); ++i)
                    std::cout << termColor[Color::ORANGE] << i << ") " << answers[i] << "\n"
                              << termColor[Color::RESET];
                std::cout << "\n";

                std::vector<std::string> correctAnswers = quiz.answers.correctAnswers;

                std::vector<int> userAnswers = getAnswersFromUser(correctAnswers.size(), answers.size());
                std::cout << "\n";
                std::cout << termColor[Color::YELLOW] << "Your answers : ";
                for (const auto &i : userAnswers)
                    std::cout << answers[i] << "   ";
                std::cout << "\n";

                std::cout << "Correct answers : ";
                for (const auto &e : correctAnswers)
                    std::cout << e << "   ";
                std::cout << "\n";

                int score = 0;
                for (const auto &userInput : userAnswers)
                {
                    if (std::find(correctAnswers.begin(), correctAnswers.end(), answers[userInput]) != correctAnswers.end())
                        score += 1;
                }

                std::cout << "\n";
                std::cout << termColor[Color::GREEN] << "Your score : " << score << "/" << correctAnswers.size() << "\n";
                std::cout << "_________________________________________________________________________________________";
                std::cout << "\n\n\n";
            }
            char isExit;
            std::cout << termColor[Color::RESET] << "Type `c` to continue or [`q` or any char] to quit : ";
            std::cin >> isExit;
            if (isExit == 'c')
                continue;
            exit(1);
        }
    }
};
int main()
{
    Exam exam(
        std::vector<MultipleChoiceQuiz>{
            MultipleChoiceQuiz{
                0,
                "Best programming languages?",
                Answer{
                    std::vector<std::string>{"C++", "Java", "Rust", "Python"},
                    std::vector<std::string>{"Brainfuck", "Scratch"},
                },
                Complexity::DIFFICULT},
            MultipleChoiceQuiz{
                1,
                "Linus Torvalds?",
                Answer{
                    std::vector<std::string>{"Programmer", "Scientist"},
                    std::vector<std::string>{"Programm", "Builder"},
                },
                Complexity::MEDIUM}});
    exam.debug(true);
    exam.conduct();
}
