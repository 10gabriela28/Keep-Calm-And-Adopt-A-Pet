
#include <QApplication>
#include <QInputDialog>
#include "gui.h"
#include "csvrepup.h"
#include "htmlrepup.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QStringList options;
    options << "CSV" << "HTML";
    bool ok;
    QString choice = QInputDialog::getItem(nullptr, "Select Format", "Format:", options, 0, false, &ok);

    if (!ok) return 0;

    Repository* r;
    Repository* ad;
    std::string type = choice.toLower().toStdString();

    if (type == "html") {
        r = new HTMLRepo("dogs.html");
        ad = new HTMLRepo("adopted_dogs.html");
    } else {
        r = new CSVRepo("dogs.csv");
        ad = new CSVRepo("adopted_dogs.csv");
    }

    Service* s = new Service(r);
    Service* as = new Service(ad);
    s->forceReset();

    QStringList options2;
    options2 << "Administrator" << "User";
    bool ok2;
    QString choice2 = QInputDialog::getItem(nullptr, "You're logging in as...", "Profile:", options2, 0, false, &ok2);
    if (!ok2) return 0;

    std::string mode = choice2.toStdString();

    GUI gui{ mode, s, as, type };
    gui.show();

    return a.exec();
}