#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

Notepad::~Notepad()
{
    delete ui;
}


void Notepad::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void Notepad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void Notepad::on_actionSave_triggered()
{
    QString fileName;

    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::on_actionExit_triggered()
{
    QApplication::quit();
}

void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void Notepad::on_actionFont_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}

void Notepad::on_actionBold_triggered(bool bold)
{
    bold ? ui->textEdit->setFontWeight(QFont::Bold) :
           ui->textEdit->setFontWeight(QFont::Normal);
}

void Notepad::on_actionUnderline_triggered(bool underline)
{
    ui->textEdit->setFontUnderline(underline);
}

void Notepad::on_actionItalic_triggered(bool italic)
{
    ui->textEdit->setFontItalic(italic);
}

void Notepad::on_actionAbout_Author_triggered()
{
    QMessageBox::about(this,
        tr("About Author"),
        tr(
            "<h3>About Author</h3>"
            "<b>Breno Baptista</b>"
            "<br>"
            "I'm a full-stack developer based in Fortaleza, Brazil. "
            "I work remotely at Massive, where we develop alternatives to fight intrusive advertising. "
            "I'm interested in GNU/Linux, shell scripting, open-source software, privacy and front end web technologies."
            "<br><br>"
            "<b>Social</b>"
            "<br>"
            "Website: <a href='https://brenobaptista.vercel.app/'>https://brenobaptista.vercel.app/</a>"
            "<br>"
            "GitHub: <a href='https://github.com/brenobaptista/'>https://github.com/brenobaptista/</a>"
            "<br>"
            "Email: <a href='mailto:brenobaptista@protonmail.com'>brenobaptista@protonmail.com</a>"
        )
    );
}

void Notepad::on_actionAbout_License_triggered()
{
    QMessageBox::about(this,
        tr("About License"),
        tr(
            "<h3>About License</h3>"
            "This project is licensed under the <b>GPL-3.0 License</b>."
            "<br>"
            "You can learn more about this license "
            "<a href='https://www.gnu.org/licenses/gpl-3.0.en.html'>here</a>."
        )
    );
}

void Notepad::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}
