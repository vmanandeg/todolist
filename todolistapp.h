#ifndef TODOLISTAPP_H
#define TODOLISTAPP_H

#include <QMainWindow>

class TodoListApp : public QMainWindow {
    Q_OBJECT

public:
    TodoListApp(QWidget *parent = nullptr);

private:
    // Algorithm 1: Sort tasks by priority
    static bool prioritySort(const QStringList &task1, const QStringList &task2);

    // Algorithm 2: Filter tasks by status
    static QVector<QStringList> filterTasks(const QVector<QStringList> &tasks, const QString &status);
};

#endif // TODOLISTAPP_H
