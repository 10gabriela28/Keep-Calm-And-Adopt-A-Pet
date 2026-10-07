
#pragma once
#include "service.h"
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCoreApplication>
#include <QDir>
#include <vector>

class GUI: public QWidget {
private:
    Service* service;
    Service* adoptionService;
    std::string repoType;

    void initGUI(const std::string& mode);
    void populateList();
    void populateFilteredList(const std::vector<Dog>& filteredDogs);
    void connectSignalsAndSlots();
    int getSelectedIndex() const;

public:
    GUI(const std::string& mode, Service* s, Service* as, std::string type);

    QPushButton* switchModeBtn = nullptr;
    QListWidget* dogListWidget = nullptr;
    QLineEdit* breedEdit = nullptr;
    QLineEdit* nameEdit = nullptr;
    QLineEdit* ageEdit = nullptr;
    QLineEdit* photographEdit = nullptr;

    QPushButton* addDBtn = nullptr;
    QPushButton* updateDBtn = nullptr;

    QPushButton* filterBtn = nullptr;
    QLineEdit* breedFilter = nullptr;
    QLineEdit* ageFilter = nullptr;

    QPushButton* adoptBtn = nullptr;
    QPushButton* openFileBtn = nullptr;

    QPushButton* viewChartBtn = nullptr;

    QLabel* imagePreviewLabel = nullptr;
};