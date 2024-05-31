#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <random>

enum Languages{
    KZ,
    RU,
    EN,
};

enum Translate{
    USER_ANSWER_NUM,
    WRONG_INDEX,
    ERROR_WHILE_CHECKING_ID,
    CFG_SHUFFLE_QUESTION,
    CFG_SHUFFLE_ANSWERS,
    COMPLEXITY_EASY,
    COMPLEXITY_MEDIUM,
    COMPLEXITY_DIFFICULT,
    COMPLEXITY_NOT_SET,
    QUESTION,
    CORRECT_ANSWER,
    CORRECT_ANSWERS,
    WRONG_ANSWER,
    CORRECT_ANSWER_COUNT,
    YOUR_ANSWERS,
    YOUR_SCORE,
    TYPE_C_OR_Q_TO,
    BOOL_TRUE,
    BOOL_FALSE,
};

// Configs start

const bool SHUFFLE_ANSWERS = true;
const bool SHUFFLE_QUESTIONS = true;
const Languages UI_LANG = RU;

std::map<Languages, std::map<Translate, std::string>> translate = {
    {
        Languages::KZ, std::map<Translate, std::string>{
            {Translate::USER_ANSWER_NUM, "Жауап индексін таңдаңыз # "},
            {Translate::WRONG_INDEX, "Индекс жарамсыз. Қайталап көріңіз!"},
            {Translate::ERROR_WHILE_CHECKING_ID, "Қате: Викторина идентификаторларын тексеріңіз!"},
            {Translate::CFG_SHUFFLE_QUESTION, "Сұрақтарды араластыру = "},
            {Translate::CFG_SHUFFLE_ANSWERS, "Жауаптарды араластыру = "},
            {Translate::COMPLEXITY_EASY, "Күрделелігі : Oңай"},
            {Translate::COMPLEXITY_MEDIUM, "Күрделелігі : Орташа"},
            {Translate::COMPLEXITY_DIFFICULT, "Күрделелігі : Қиын"},
            {Translate::COMPLEXITY_NOT_SET, "The Күрделелігі орнатылмаған"},
            {Translate::QUESTION, "Сұрақ: "},
            {Translate::CORRECT_ANSWER, "Дұрыс жауап #"},
            {Translate::WRONG_ANSWER, "Қате жауап #"},
            {Translate::CORRECT_ANSWER_COUNT, "Дұрыс жауаптар саны: "},
            {Translate::YOUR_ANSWERS, "Сіздің жауаптарыңыз: "},
            {Translate::CORRECT_ANSWERS, "Дұрыс жауаптар: "},
            {Translate::YOUR_SCORE, "Сіздің ұпайыңыз: "},
            {Translate::TYPE_C_OR_Q_TO, "Жалғастыру үшін `c` немесе шығу үшін [`q` немесе кез келген таңба] теріңіз: "},
            {Translate::BOOL_TRUE, "Қосылған"},
            {Translate::BOOL_FALSE, "Өшірілген"},
        },
    },
    {
        Languages::RU, std::map<Translate, std::string>{
            {Translate::USER_ANSWER_NUM, "Выберите индекс ответа # "},
            {Translate::WRONG_INDEX, "Неверный индекс. Попробуйте еще раз!"},
            {Translate::ERROR_WHILE_CHECKING_ID, "Ошибка: Проверьте свои идентификаторы викторины!"},
            {Translate::CFG_SHUFFLE_QUESTION, "Перетасовать_вопросы = "},
            {Translate::CFG_SHUFFLE_ANSWERS, "Перетасоват_ответы = "},
            {Translate::COMPLEXITY_EASY, "Сложность: Легко"},
            {Translate::COMPLEXITY_MEDIUM, "Сложность: Средняя"},
            {Translate::COMPLEXITY_DIFFICULT, "Сложность: Сложно"},
            {Translate::COMPLEXITY_NOT_SET, "Сложность не установлена"},
            {Translate::QUESTION, "Вопрос: : "},
            {Translate::CORRECT_ANSWER, "Правильный ответ #"},
            {Translate::WRONG_ANSWER, "Неправильный ответ #"},
            {Translate::CORRECT_ANSWER_COUNT, "Количество правильных ответов: "},
            {Translate::YOUR_ANSWERS, "Ваши ответы: "},
            {Translate::CORRECT_ANSWERS, "Правильные ответы: "},
            {Translate::YOUR_SCORE, "Ваша оценка: "},
            {Translate::TYPE_C_OR_Q_TO, "Введите `c`, чтобы продолжить, или [`q` или любой символ], чтобы выйти: "},
            {Translate::BOOL_TRUE, "Активировано"},
            {Translate::BOOL_FALSE, "Неактивировано"},
        },
    },
    {
        Languages::EN, std::map<Translate, std::string>{
            {Translate::USER_ANSWER_NUM, "Choose answer index : # "},
            {Translate::WRONG_INDEX, "Wrong index. Try again!"},
            {Translate::ERROR_WHILE_CHECKING_ID, "Error : Check your quizzes IDs!"},
            {Translate::CFG_SHUFFLE_QUESTION, "SHUFFLE_QUESTION = "},
            {Translate::CFG_SHUFFLE_ANSWERS, "SHUFFLE_ANSWERS = "},
            {Translate::COMPLEXITY_EASY, "Complexity : Easy"},
            {Translate::COMPLEXITY_MEDIUM, "Complexity : Medium"},
            {Translate::COMPLEXITY_DIFFICULT, "Complexity : Difficult"},
            {Translate::COMPLEXITY_NOT_SET, "The Complexity:: is not set"},
            {Translate::QUESTION, "Question : "},
            {Translate::CORRECT_ANSWER, "Correct answer #"},
            {Translate::WRONG_ANSWER, "Wrong answer #"},
            {Translate::CORRECT_ANSWER_COUNT, "Correct answer count : "},
            {Translate::YOUR_ANSWERS, "Your answers : "},
            {Translate::CORRECT_ANSWERS, "Correct answers : "},
            {Translate::YOUR_SCORE, "Your score : "},
            {Translate::TYPE_C_OR_Q_TO, "Type `c` to continue or [`q` or any char] to quit : "},
            {Translate::BOOL_TRUE, "Active"},
            {Translate::BOOL_FALSE, "Inactive"},
        },
    },
};

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
    
    std::string bool_2_str(bool b){
        return (b) ? translate[UI_LANG][Translate::BOOL_TRUE] : translate[UI_LANG][Translate::BOOL_FALSE]; 
    }

    std::vector<int> getAnswersFromUser(int answerCount, int exclusiveHighBound)
    {
        std::set<int> result;
        for (int i = 0; i < answerCount; ++i)
        {
            int input;
            std::cout << translate[UI_LANG][Translate::USER_ANSWER_NUM] << i + 1 << ": ";
            std::cin >> input;
            if (input < 0 or input >= exclusiveHighBound or std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(32767, '\n');
                --i;
                std::cout << translate[UI_LANG][Translate::WRONG_INDEX] << "\n";
                continue;
            }
            result.insert(input);
        }
        return std::vector<int>(result.begin(), result.end());
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
            std::cout << translate[UI_LANG][Translate::ERROR_WHILE_CHECKING_ID] << "\n";
            for (const auto &quiz : quizzes)
                std::cout << quiz.id << "   ";
            exit(1);
        }
    }

    void debug(bool printable)
    {
        std::string log = "";

        log.append(translate[UI_LANG][Translate::CFG_SHUFFLE_QUESTION] + bool_2_str(SHUFFLE_QUESTIONS) + "\n");
        log.append(translate[UI_LANG][Translate::CFG_SHUFFLE_ANSWERS] + bool_2_str(SHUFFLE_ANSWERS) + "\n");

        for (const auto &quiz : quizzes)
        {
            // id
            log += std::string("id : " + to_str(quiz.id) + "\n");

            // complexity
            switch (quiz.complexity)
            {
            case Complexity::EASY:
                log += std::string(translate[UI_LANG][Translate::COMPLEXITY_EASY] + "\n");
                break;
            case Complexity::MEDIUM:
                log += std::string(translate[UI_LANG][Translate::COMPLEXITY_MEDIUM] + "\n");
                break;
            case Complexity::DIFFICULT:
                log += std::string(translate[UI_LANG][Translate::COMPLEXITY_DIFFICULT] + "\n");
                break;
            default:
                std::cerr << translate[UI_LANG][Translate::COMPLEXITY_NOT_SET];
                exit(1);
            }
            // question
            log += std::string(translate[UI_LANG][Translate::QUESTION] + quiz.question + "\n");

            // answers
            for (int i = 0; i < quiz.answers.correctAnswers.size(); ++i)
                log += std::string(translate[UI_LANG][Translate::CORRECT_ANSWER] + to_str(i) + " " + quiz.answers.correctAnswers[i] + "\n");
            for (int i = 0; i < quiz.answers.wrongAnswers.size(); ++i)
                log += std::string(translate[UI_LANG][Translate::WRONG_ANSWER] + to_str(i) + " " + quiz.answers.wrongAnswers[i] + "\n");
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
            // Generate quiz index for default or shuffled
            std::vector<int> quiz_indexes;
            quiz_indexes.reserve(quizzes.size());
            for (int i = 0; i < quizzes.size(); ++i)
                quiz_indexes.push_back(i);
            if (SHUFFLE_QUESTIONS)
                shuffleVector(quiz_indexes);

            // Start exam...
            for (const auto &quiz_it : quiz_indexes)
            {
                MultipleChoiceQuiz quiz = quizzes[quiz_it];

                std::cout << termColor[Color::BLUE] << "id: " << quiz.id << ") " << quiz.question << "    " << termColor[Color::CYAN];
                switch (quiz.complexity)
                {
                case Complexity::EASY:
                    std::cout << translate[UI_LANG][Translate::COMPLEXITY_EASY] << "\n";
                    break;
                case Complexity::MEDIUM:
                    std::cout << translate[UI_LANG][Translate::COMPLEXITY_MEDIUM] << "\n";
                    break;
                case Complexity::DIFFICULT:
                    std::cout << translate[UI_LANG][Translate::COMPLEXITY_DIFFICULT] << "\n";
                    break;
                default:
                    std::cerr << translate[UI_LANG][Translate::COMPLEXITY_NOT_SET];
                    exit(1);
                }

                std::vector<std::string> answers;
                if (SHUFFLE_ANSWERS)
                    answers = quiz.answers.getShuffled();
                else
                    answers = quiz.answers.getAnswers();

                std::cout << termColor[Color::RESET] << "\n";
                for (int ans_i = 0; ans_i < answers.size(); ++ans_i)
                    std::cout << termColor[Color::ORANGE] << ans_i << ") " << answers[ans_i] << "\n"
                              << termColor[Color::RESET];
                std::cout << "\n";

                std::vector<std::string> correctAnswers = quiz.answers.correctAnswers;

                std::cout << translate[UI_LANG][Translate::CORRECT_ANSWER_COUNT] << correctAnswers.size() << "\n";
                std::vector<int> userAnswers = getAnswersFromUser(correctAnswers.size(), answers.size());
                std::cout << "\n";
                std::cout << termColor[Color::YELLOW] << translate[UI_LANG][Translate::YOUR_ANSWERS];
                for (const auto &i : userAnswers)
                    std::cout << answers[i] << "   ";
                std::cout << "\n";

                std::cout << translate[UI_LANG][Translate::CORRECT_ANSWERS];
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
                std::cout << termColor[Color::GREEN] << translate[UI_LANG][Translate::YOUR_SCORE] << score << "/" << correctAnswers.size() << "\n";
                std::cout << "_________________________________________________________________________________________";
                std::cout << "\n\n\n";
            }
            char isExit;
            std::cout << termColor[Color::RESET] << translate[UI_LANG][Translate::TYPE_C_OR_Q_TO];
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
                Complexity::MEDIUM},
            MultipleChoiceQuiz{
                2,
                "MS-DOS ОЖ-де файл атауындағы таңбалардың максималды саны",
                Answer{
                    std::vector<std::string>{"8"},
                    std::vector<std::string>{"255", "256", "10", "12"},
                },
                Complexity::EASY},
            MultipleChoiceQuiz{
                3,
                "Операциялық жүйелер құрамына мыналар кіреді:",
                Answer{
                    std::vector<std::string>{"жүйелік бағдарламалық қамтамасыз ету"},
                    std::vector<std::string>{"қолданбалы бағдарламалық қамтамасыз ету",
                                             "бағдарламалау жүйелері",
                                             "деректер базасын басқару жүйелері",
                                             "бірегей бағдарламалық қамтамасыз ету"
                    },
                },
                Complexity::EASY},
            MultipleChoiceQuiz{
                4,
                "WINDOWS операциялық жүйесі келесі функцияны орындамайды",
                Answer{
                    std::vector<std::string>{"бағдарламалық жүйелерді құру"},
                    std::vector<std::string>{"қолданбалы бағдарламаларды іске қосу",
                                             "файлдық жүйемен жұмыс істеуді қамтамасыз ету",
                                             "компьютердің аппараттық құралдарын басқару",
                                             "бірнеше қосымшалардың бір уақытта жұмыс істеуін қамтамасыз етеді"
                    },
                },
                Complexity::EASY},
            MultipleChoiceQuiz{
                5,
                "Сommand.com бағдарламасы ...",
                Answer{
                    std::vector<std::string>{"пайдаланушы енгізген командаларды өңдейді"},
                    std::vector<std::string>{"операциялық жүйенің барлық командаларын сақтайды",
                                             "командалар мен бағдарламаларды өңдейді",
                                             "барлық командаларды өз жұмысында сақтайды",
                                             "дискіні пішімдейді"
                    },
                },
                Complexity::EASY},
            MultipleChoiceQuiz{
                6,
                "Жедел жадтың жылдамдығы немен өлшенеді",
                Answer{
                    std::vector<std::string>{"наносекундпен"},
                    std::vector<std::string>{"миллисекундпен",
                                             "секундтармен",
                                             "мегагерцпен",
                                             "гигагерцпен"
                    },
                },
                Complexity::EASY},

        });
    exam.debug(true);
    exam.conduct();
}
