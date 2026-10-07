
#include "gui.h"
#include <qlayout.h>
#include <qformlayout.h>
#include <qmessagebox.h>
#include <qdesktopservices.h>
#include <qurl.h>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <algorithm>
#include <vector>
#include <QInputDialog>
#include <QProgressBar>
#include <map>

GUI::GUI(const std::string& mode, Service* s, Service* as, std::string type) : service{s}, adoptionService{as}, repoType{type} {
    this->initGUI(mode);
    this->populateList();
    this->connectSignalsAndSlots();
}

void GUI::initGUI(const std::string& mode) {
    QHBoxLayout* mainLayout = new QHBoxLayout{ this };

    this->dogListWidget = new QListWidget{};
    mainLayout->addWidget(this->dogListWidget);

    QVBoxLayout* rightLayout = new QVBoxLayout{};
    mainLayout->addLayout(rightLayout);

    QFormLayout* dogForm = new QFormLayout{};
    this->breedEdit = new QLineEdit{};
    this->nameEdit = new QLineEdit{};
    this->ageEdit = new QLineEdit{};
    this->photographEdit = new QLineEdit{};

    this->imagePreviewLabel = new QLabel{};
    this->imagePreviewLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    this->imagePreviewLabel->setAlignment(Qt::AlignCenter);
    this->imagePreviewLabel->setFixedSize(300, 200);

    dogForm->addRow("Breed:", this->breedEdit);
    dogForm->addRow("Name:", this->nameEdit);
    dogForm->addRow("Age:", this->ageEdit);
    dogForm->addRow("Photo:", this->photographEdit);
    dogForm->addRow("Preview:", this->imagePreviewLabel);
    rightLayout->addLayout(dogForm);

    if (mode == "Administrator") {
        this->addDBtn = new QPushButton{ "Add Dog" };
        this->updateDBtn = new QPushButton{ "Update Dog" };

        rightLayout->addWidget(this->addDBtn);
        rightLayout->addWidget(this->updateDBtn);
    }
    else {
        this->filterBtn = new QPushButton{ "Filter by Breed & Age" };
        this->adoptBtn = new QPushButton{ "Adopt Selected Dog" };
        this->openFileBtn = new QPushButton{ "View Adoption List" };
        this->viewChartBtn = new QPushButton{ "View Breed Statistics Chart" };

        this->breedFilter = new QLineEdit{};
        this->breedFilter->setPlaceholderText("Filter Breed...");
        this->ageFilter = new QLineEdit{};
        this->ageFilter->setPlaceholderText("Filter Max Age...");

        rightLayout->addWidget(this->filterBtn);
        rightLayout->addWidget(this->breedFilter);
        rightLayout->addWidget(this->ageFilter);
        rightLayout->addWidget(this->adoptBtn);
        rightLayout->addWidget(this->openFileBtn);
        rightLayout->addWidget(this->viewChartBtn);
    }

    this->switchModeBtn = new QPushButton{ "Switch Mode" };
    rightLayout->addWidget(this->switchModeBtn);
}

void GUI::populateList() {
    this->dogListWidget->clear();
    auto allDogs = this->service->getAll();
    for (const auto& d : allDogs) {
        this->dogListWidget->addItem(QString::fromStdString(d.getName() + " | " + d.getBreed()));
    }
}

void GUI::populateFilteredList(const std::vector<Dog>& filteredDogs) {
    this->dogListWidget->clear();
    for (const auto& d : filteredDogs) {
        this->dogListWidget->addItem(QString::fromStdString(d.getName() + " | " + d.getBreed()));
    }
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->dogListWidget, &QListWidget::itemSelectionChanged, [this]() {
        int idx = this->getSelectedIndex();
        if (idx < 0) return;

        Dog d = this->service->getDogS(idx);

        this->breedEdit->setText(QString::fromStdString(d.getBreed()));
        this->nameEdit->setText(QString::fromStdString(d.getName()));
        this->ageEdit->setText(QString::number(d.getAge()));
        this->photographEdit->setText(QString::fromStdString(d.getPhotograph()));

        std::string path = d.getPhotograph();
        std::string dogName = d.getName();
        std::string fileName = "";

        if (dogName == "Lucky") fileName = "amstaff.png";
        else if (dogName == "Larry") fileName = "dachshund.png";
        else if (dogName == "Daring") fileName = "mallinois.png";
        else if (dogName == "Aurora") fileName = "husky.png";
        else if (dogName == "Pooma" || dogName == "no") fileName = "maltesepoodle.png";
        else if (dogName == "Buddy") fileName = "labrador.png";
        else if (dogName == "Freddy") fileName = "dwarfschnauzer.png";
        else if (dogName == "Nugget") fileName = "goldenretriever.png";
        else if (dogName == "Alphie") fileName = "mixedbreed.png";
        else if (dogName == "Bellus") fileName = "bucovinashepherd.png";
        else if (dogName == "Teddy") fileName = "pug.png";
        else {
            size_t lastSlash = path.find_last_of("/\\");
            fileName = (lastSlash != std::string::npos) ? path.substr(lastSlash + 1) : path;
        }

        QString relativeTarget = "puppies/" + QString::fromStdString(fileName);
        QString appDir = QCoreApplication::applicationDirPath();

        QString path1 = relativeTarget;
        QString path2 = appDir + "/puppies/" + QString::fromStdString(fileName);
        QString path3 = QDir(appDir).filePath("../puppies/" + QString::fromStdString(fileName));
        QString path4 = QDir(appDir).filePath("../../puppies/" + QString::fromStdString(fileName));

        QPixmap pixmap;
        if (QFile::exists(path1)) pixmap.load(path1);
        else if (QFile::exists(path2)) pixmap.load(path2);
        else if (QFile::exists(path3)) pixmap.load(path3);
        else if (QFile::exists(path4)) pixmap.load(path4);

        if (!pixmap.isNull()) {
            this->imagePreviewLabel->setPixmap(pixmap.scaled(this->imagePreviewLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            this->imagePreviewLabel->setText("No image preview available");
        }
    });

    if (this->addDBtn) {
        QObject::connect(this->addDBtn, &QPushButton::clicked, [this]() {
            QString ageText = this->ageEdit->text();
            bool ok;
            int a = ageText.toInt(&ok);
            if (!ok) {
                QMessageBox::critical(this, "ERROR", "Age must be a valid number!");
                return;
            }
            std::string b = this->breedEdit->text().toStdString();
            std::string n = this->nameEdit->text().toStdString();
            std::string p = this->photographEdit->text().toStdString();
            try {
                this->service->addDogS(Dog(b, n, a, p));
                this->populateList();
            } catch (std::exception& e) {
                QMessageBox::critical(this, "ERROR", e.what());
            }
        });
    }

    if (this->updateDBtn) {
        QObject::connect(this->updateDBtn, &QPushButton::clicked, [this]() {
            int idx = this->getSelectedIndex();
            if (idx < 0) {
                QMessageBox::warning(this, "ERROR", "Please select a dog to update!");
                return;
            }

            bool ok;
            int a = this->ageEdit->text().toInt(&ok);
            if (!ok) {
                QMessageBox::critical(this, "ERROR", "The age must be a number!");
                return;
            }

            std::string b = this->breedEdit->text().toStdString();
            std::string n = this->nameEdit->text().toStdString();
            std::string p = this->photographEdit->text().toStdString();

            try {
                this->service->updateBreed(b, idx);
                this->service->updateName(n, idx);
                this->service->updateAge(a, idx);
                this->service->updatePhoto(p, idx);

                this->populateList();
                this->dogListWidget->setCurrentRow(idx);
            } catch (std::exception& e) {
                QMessageBox::critical(this, "ERROR", e.what());
            }
        });
    }

    if (this->filterBtn) {
        QObject::connect(this->filterBtn, &QPushButton::clicked, [this]() {
            QString targetBreed = this->breedFilter->text();
            QString ageText = this->ageFilter->text();

            if (targetBreed.isEmpty() || ageText.isEmpty()) {
                this->populateList();
                return;
            }

            bool ok;
            int maxAge = ageText.toInt(&ok);
            if (!ok) {
                QMessageBox::critical(this, "ERROR", "Age filter must be a valid number!");
                return;
            }

            std::vector<Dog> matches;
            auto allDogs = this->service->getAll();

            for (int i = 0; i < allDogs.getSize(); ++i) {
                Dog d = this->service->getDogS(i);
                if (d.getBreed() == targetBreed.toStdString() && d.getAge() < maxAge) {
                    matches.push_back(d);
                }
            }
            this->populateFilteredList(matches);
        });
    }

    if (this->adoptBtn) {
        QObject::connect(this->adoptBtn, &QPushButton::clicked, [this]() {
            int idx = this->getSelectedIndex();
            if (idx < 0) return;
            Dog d = this->service->getDogS(idx);
            this->adoptionService->addDogS(d);
            this->service->deleteDogS(d);
            this->populateList();
        });
    }

    if (this->openFileBtn) {
        QObject::connect(this->openFileBtn, &QPushButton::clicked, [this]() {
            if (this->repoType == "html") system("start adopted_dogs.html");
            else system("start adopted_dogs.csv");
        });
    }

    if (this->viewChartBtn) {
        QObject::connect(this->viewChartBtn, &QPushButton::clicked, [this]() {
            std::map<std::string, int> counts;
            auto allDogs = this->service->getAll();
            int maxCount = 1;

            for (int i = 0; i < allDogs.getSize(); ++i) {
                counts[this->service->getDogS(i).getBreed()]++;
                if (counts[this->service->getDogS(i).getBreed()] > maxCount) {
                    maxCount = counts[this->service->getDogS(i).getBreed()];
                }
            }

            QWidget* chartWindow = new QWidget();
            chartWindow->setWindowTitle("Breed Statistics Chart");
            chartWindow->resize(500, 350);
            chartWindow->setAttribute(Qt::WA_DeleteOnClose);

            QHBoxLayout* chartLayout = new QHBoxLayout{ chartWindow };

            for (auto const& [breed, count] : counts) {
                QVBoxLayout* column = new QVBoxLayout{};

                QProgressBar* bar = new QProgressBar{};
                bar->setOrientation(Qt::Vertical);
                bar->setRange(0, maxCount);
                bar->setValue(count);
                bar->setFormat(QString::number(count));
                bar->setTextVisible(true);

                bar->setStyleSheet("QProgressBar::chunk { background-color: #2E75B6; }");

                QLabel* label = new QLabel{ QString::fromStdString(breed) };
                label->setAlignment(Qt::AlignCenter);

                column->addWidget(bar, 1);
                column->addWidget(label);
                chartLayout->addLayout(column);
            }

            chartWindow->show();
        });
    }

    if (this->switchModeBtn) {
        QObject::connect(this->switchModeBtn, &QPushButton::clicked, [this]() {
            QStringList options2;
            options2 << "Administrator" << "User";
            bool ok2;
            QString choice2 = QInputDialog::getItem(this, "You're logging in as...", "Profile:", options2, 0, false, &ok2);

            if (!ok2) return;

            std::string newMode = choice2.toStdString();

            if (this->dogListWidget) this->dogListWidget->deleteLater();
            if (this->breedEdit) this->breedEdit->deleteLater();
            if (this->nameEdit) this->nameEdit->deleteLater();
            if (this->ageEdit) this->ageEdit->deleteLater();
            if (this->photographEdit) this->photographEdit->deleteLater();
            if (this->imagePreviewLabel) this->imagePreviewLabel->deleteLater();

            if (this->addDBtn) this->addDBtn->deleteLater();
            if (this->updateDBtn) this->updateDBtn->deleteLater();
            if (this->filterBtn) this->filterBtn->deleteLater();
            if (this->breedFilter) this->breedFilter->deleteLater();
            if (this->ageFilter) this->ageFilter->deleteLater();
            if (this->adoptBtn) this->adoptBtn->deleteLater();
            if (this->openFileBtn) this->openFileBtn->deleteLater();
            if (this->viewChartBtn) this->viewChartBtn->deleteLater();
            if (this->switchModeBtn) this->switchModeBtn->deleteLater();


            if (this->layout()) {
                QLayoutItem* item;
                while ((item = this->layout()->takeAt(0)) != nullptr) {
                    delete item;
                }
                delete this->layout();
            }

            // Zero out structural pointers before re-initializing
            this->addDBtn = nullptr;
            this->updateDBtn = nullptr;
            this->filterBtn = nullptr;
            this->breedFilter = nullptr;
            this->ageFilter = nullptr;
            this->adoptBtn = nullptr;
            this->openFileBtn = nullptr;
            this->viewChartBtn = nullptr;
            this->switchModeBtn = nullptr;

            this->initGUI(newMode);
            this->populateList();
            this->connectSignalsAndSlots();
        });
    }
}

int GUI::getSelectedIndex() const {
    int selection = this->dogListWidget->currentRow();
    return selection;
}