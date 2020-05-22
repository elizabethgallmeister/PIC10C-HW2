#include "mainwindow.h"
#include "ui_mainwindow.h"

QHBoxLayout* MainWindow::makeunit(int i)
{
    QLabel* l2 = new QLabel();
    switch(i) {
        case 1 : l2 -> setText("Homework 1");
                 break;
        case 2 : l2 -> setText("Homework 2");
                 break;
        case 3 : l2 -> setText("Homework 3");
                 break;
        case 4 : l2 -> setText("Homework 4");
                 break;
        case 5 : l2 -> setText("Homework 5");
                 break;
        case 6 : l2 -> setText("Homework 6");
                 break;
        case 7 : l2 -> setText("Homework 7");
                 break;
        case 8 : l2 -> setText("Homework 8");
                 break;
        case 9 : l2 -> setText("Midterm 1");
                 break;
        case 10 : l2 -> setText("Midterm 2");
                  break;
        case 11 : l2 -> setText("Final Exam");
                  break;
    }

    QSlider* slide1 = new QSlider(Qt::Horizontal);
    slide1 -> setRange(0, 100);

    QSpinBox* box1 = new QSpinBox();
    box1 -> setRange(0,100);
    std::cout << box1 -> value();

    QObject::connect(slide1, SIGNAL(valueChanged(int)),
                    box1, SLOT(setValue(int)));
    QObject::connect(box1, SIGNAL(valueChanged(int)),
                    slide1, SLOT(setValue(int)));
    grades.push_back(box1);

    QHBoxLayout* layout = new QHBoxLayout();
    layout -> addWidget(l2);
    layout -> addWidget(slide1);
    layout -> addWidget(box1);

    return layout;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* window = new QWidget;
    window -> setWindowTitle("Final Grade Calculator");

    QComboBox* classes = new QComboBox();
    classes -> addItem("PIC 10B: Intermediate Programming");
    classes -> addItem("Math 61: Discrete Math");
    QLabel* course = new QLabel("Course:");

    QHBoxLayout* header = new QHBoxLayout();
    header -> addWidget(course);
    header -> addWidget(classes);

    QVBoxLayout* outmost = new QVBoxLayout();
    outmost -> addLayout(header);

    QVBoxLayout* col1 = new QVBoxLayout();
    for(int i = 1; i < 9; ++i)
    {
        col1 -> addLayout(makeunit(i));
    }

    QRadioButton* schemeA = new QRadioButton("Schema A");
    QRadioButton* schemeB = new QRadioButton("Schema B");

    calc2 = new QLabel("Your Grade: 0.0");
    calculate = new QPushButton("Calculate my grade!");

    QVBoxLayout* col2 = new QVBoxLayout();
    col2 -> addLayout(makeunit(9));
    col2 -> addLayout(makeunit(10));
    col2 -> addLayout(makeunit(11));
    col2 -> addWidget(schemeA);
    col2 -> addWidget(schemeB);
    col2 -> addWidget(calculate);
    col2 -> addWidget(calc2);

    QObject::connect(calculate, &QPushButton::clicked,
                     this, &MainWindow::buttonClicked);

    QObject::connect(schemeB, SIGNAL(toggled(bool)),
                     this, SLOT(getGrade(bool)));

    QHBoxLayout* overall = new QHBoxLayout();
    overall -> addLayout(col1);
    overall -> addLayout(col2);

    outmost -> addLayout(overall);

    window -> setLayout(outmost);
    setCentralWidget(window);
}

void MainWindow::buttonClicked()
{
    ++count;
    if( count % 2 == 0)
        calculate -> setText("Calculate my grade!");
    else
    {
        QString text = "Your Grade: " + QString::number( finalGrade );
        calculate -> setText(text);
    }
}

void MainWindow::getGrade(bool checked)
{
    if(checked) schemeA = false;
    int hwScore = 0;
    std::vector<int> hwScores(0);
    for(size_t i = 0; i < 8; ++i)
    {
        hwScores.push_back(grades[i]->value());
        std::cout<< grades[i]->value() << std::endl;
    }
    sort(hwScores.begin(), hwScores.end());
    if(schemeA)
    {
        for(size_t i = 0; i < hwScores.size()-1; ++i)
            hwScore += hwScores[i];
        finalGrade = (0.25*hwScore) + (.20*(grades[8]->value())) + (.20*(grades[9]->value())) + (.35*(grades[10]->value()));
    }
    else
    {
        for(size_t i = 0; i < hwScores.size()-1; ++i)
            hwScore += hwScores[i];
        finalGrade = (0.25*hwScore/7) + (0.44*(grades[10]->value()));
        if(grades[8]->value() > grades[9]->value()) finalGrade += 0.30*(grades[8]->value());
        else    finalGrade += 0.30*(grades[9]->value());
    }
}

MainWindow::~MainWindow()
{

}
