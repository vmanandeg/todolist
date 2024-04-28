#include "todolistapp.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QComboBox>
#include <QStringListModel>

bool TodoListApp::prioritySort(const QStringList &task1, const QStringList &task2) {
    QStringList priorities = {"High", "Medium", "Low"};
    return priorities.indexOf(task1[1]) < priorities.indexOf(task2[1]);
}

QVector<QStringList> TodoListApp::filterTasks(const QVector<QStringList> &tasks, const QString &status) {
    QVector<QStringList> filteredTasks;
    for (const QStringList &task : tasks) {
        if (task[2] == status) {
            filteredTasks.append(task);
        }
    }
    return filteredTasks;
}

TodoListApp::TodoListApp(QWidget *parent) : QMainWindow(parent) {
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::darkMagenta);
    setStyleSheet(QString("QMainWindow { background: qlineargradient(y1:0, y2:1, stop:0 white, stop:1 darkmagenta); }"
                          "QLineEdit { background-color: transparent; color: black; }"
                          "QPushButton { background-color: transparent; border: none; border-radius: 10px; padding: 5px; }"));

    QLabel *taskLabel = new QLabel("Task:");
    taskLabel->setStyleSheet("font-weight: bold; color: black;");
    QLineEdit *taskInput = new QLineEdit;

    QLabel *priorityLabel = new QLabel("Priority:");
    priorityLabel->setStyleSheet("font-weight: bold; color: black;");
    QComboBox *priorityInput = new QComboBox;
    priorityInput->addItems({"High", "Medium", "Low"});

    QLabel *statusLabel = new QLabel("Status:");
    statusLabel->setStyleSheet("font-weight: bold; color: black;");
    QComboBox *statusInput = new QComboBox;
    statusInput->addItems({"Complete", "In Progress", "Not Started"});

    QPushButton *addButton = new QPushButton("Add Task");
    addButton->setStyleSheet("border-radius: 10px; padding: 5px;"); // Rounded corners and padding

    QTableWidget *taskTable = new QTableWidget;
    taskTable->setColumnCount(3);
    taskTable->setHorizontalHeaderLabels(QStringList() << "Task" << "Priority" << "Status");
    taskTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(addButton, &QPushButton::clicked, this, [=]() {
        int rowCount = taskTable->rowCount();
        taskTable->insertRow(rowCount);
        taskTable->setItem(rowCount, 0, new QTableWidgetItem(taskInput->text()));

        QComboBox *priorityCombo = new QComboBox;
        priorityCombo->addItems({"High", "Medium", "Low"});
        priorityCombo->setCurrentText(priorityInput->currentText());
        taskTable->setCellWidget(rowCount, 1, priorityCombo);

        QComboBox *statusCombo = new QComboBox;
        statusCombo->addItems({"Complete", "In Progress", "Not Started"});
        statusCombo->setCurrentText(statusInput->currentText());
        taskTable->setCellWidget(rowCount, 2, statusCombo);

        taskInput->clear();

        QVector<QStringList> tasks;
        for (int row = 0; row < taskTable->rowCount(); ++row) {
            QStringList task = {
                taskTable->item(row, 0)->text(),
                taskTable->cellWidget(row, 1)->property("currentText").toString(),
                taskTable->cellWidget(row, 2)->property("currentText").toString()
            };
            tasks.append(task);
        }
        std::sort(tasks.begin(), tasks.end(), prioritySort);

        taskTable->clearContents();
        for (int row = 0; row < tasks.size(); ++row) {
            taskTable->setItem(row, 0, new QTableWidgetItem(tasks[row][0]));

            QComboBox *priorityCombo = new QComboBox;
            priorityCombo->addItems({"High", "Medium", "Low"});
            priorityCombo->setCurrentText(tasks[row][1]);
            taskTable->setCellWidget(row, 1, priorityCombo);

            QComboBox *statusCombo = new QComboBox;
            statusCombo->addItems({"Complete", "In Progress", "Not Started"});
            statusCombo->setCurrentText(tasks[row][2]);
            taskTable->setCellWidget(row, 2, statusCombo);
        }
    });

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(taskLabel);
    mainLayout->addWidget(taskInput);
    mainLayout->addWidget(priorityLabel);
    mainLayout->addWidget(priorityInput);
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(statusInput);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(taskTable);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}
