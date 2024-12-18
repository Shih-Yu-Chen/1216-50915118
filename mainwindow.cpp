#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

// MainWindow 類別的建構函式
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 將選單中的動作連結到 saveToFile 函式
    connect(ui->action_5, &QAction::triggered, this, &MainWindow::saveToFile);
}

// MainWindow 類別的解構函式
MainWindow::~MainWindow()
{
    delete ui;
}

// saveToFile 函式：用於保存文字到檔案
void MainWindow::saveToFile()
{
    // 開啟文件儲存對話框以獲取檔案名稱
    QString fileName = QFileDialog::getSaveFileName(this, tr("儲存檔案"), "", tr("文字檔案 (*.txt);;所有檔案 (*)"));

    if (fileName.isEmpty()) {
        return; // 如果使用者未選擇檔案名稱則返回
    }

    // 嘗試開啟檔案以進行寫入操作
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("錯誤"), tr("無法開啟檔案進行寫入：%1").arg(file.errorString()));
        return; // 如果檔案無法開啟則返回
    }

    // 使用 QTextStream 寫入文字
    QTextStream out(&file);
    out << ui->textEdit->toPlainText(); // 將 textEdit 中的文字內容寫入檔案
    file.close(); // 關閉檔案

    // 顯示檔案儲存成功的訊息框
    QMessageBox::information(this, tr("成功"), tr("檔案儲存成功！"));
}
