// Testing Build

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Functions/file_modes.h"
#include <QProcess>

QString ResFilename; // инициализация переменной для проверки файла
QPlainTextEdit* MainWindow::debugTextEdit = nullptr; // Инициализация статической переменной debugTextEdit

// UI interface intialization
MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	setFixedSize(618, 380); // Установка фиксированного размера окна

	Ui_mainWindow ui; // Создание объекта класса Ui_mainWindow
	ui.setupUi(this); // Настройка пользовательского интерфейса

	// Получение указателей на виджеты из загруженного .ui файла
	filenameLineEdit = findChild<QLineEdit*>("filenameLineEdit");
	browseButton = findChild<QPushButton*>("browseButton");
	modeComboBox = findChild<QComboBox*>("modeComboBox");
	unpackButton = findChild<QPushButton*>("unpackButton");
	packModeComboBox = findChild<QComboBox*>("packModeComboBox");
	makeResButton = findChild<QPushButton*>("makeResButton");
	debugTextEdit = findChild<QPlainTextEdit*>("debugTextEdit");
	checkBox = findChild<QCheckBox*>("checkBox");

	// принудительно ставим режим чтобы показать его описание при первом запуске
	modeComboBox->setCurrentText("as1_engine");
	handleModeComboBoxChanged("as1_engine");
	// список режимов распаковки
	modeComboBox->addItem("as1_engine");
	modeComboBox->addItem("theseus_pc");
	modeComboBox->addItem("as1world");
	modeComboBox->addItem("zs1");
	modeComboBox->addItem("zs1_mobile");
	modeComboBox->addItem("as2_original");
	modeComboBox->addItem("as2_addons");
	modeComboBox->addItem("zs2_engine");
	modeComboBox->addItem("as2legend_engine");
	modeComboBox->addItem("oe_engine");
	modeComboBox->addItem("crazylunch");
	modeComboBox->addItem("chackstemple");
	modeComboBox->addItem("locoland");
	// список режимов упаковки
	packModeComboBox->addItem("AS/ZS Engine");
	packModeComboBox->addItem("Objects Extended Engine");
	packModeComboBox->addItem("Locoland Engine");

	alternativeModeEnabled = false; // Установка начального значения alternativeModeEnabled в false

	// Проверка начального состояния чекбокса и установка alternativeModeEnabled
	if (checkBox->isChecked()) {
		alternativeModeEnabled = true;
	}

	// Подключение обработчиков событий
	connect(browseButton, &QPushButton::clicked, this, &MainWindow::handleBrowseButtonClicked);
	connect(unpackButton, &QPushButton::clicked, this, &MainWindow::handleUnpackButtonClicked);
	connect(modeComboBox, QOverload<const QString&>::of(&QComboBox::currentTextChanged), this, &MainWindow::handleModeComboBoxChanged);
	connect(packModeComboBox, QOverload<const QString&>::of(&QComboBox::currentTextChanged), this, &MainWindow::handlePackModeComboBoxChanged);
	connect(makeResButton, &QPushButton::clicked, this, &MainWindow::handleMakeResButtonClicked);
	connect(checkBox, &QCheckBox::stateChanged, this, &MainWindow::handleCheckBoxStateChanged);

	qInstallMessageHandler(myMessageOutput); // Устанавливаем обработчик сообщений для qDebug
}

MainWindow::~MainWindow()
{
	delete ui;
}

// CheckBox Functional
void MainWindow::handleCheckBoxStateChanged(int state)
{
	alternativeModeEnabled = (state == Qt::Checked);
	if (!alternativeModeEnabled) {
		alternativeModeEnabled = false; // Установите значение в false, если галочка не установлена
	}
}

// debugtextedit functional
void MainWindow::myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
	QByteArray localMsg = msg.toLocal8Bit();
	switch (type) {
	case QtDebugMsg:
		if (debugTextEdit != nullptr) // Проверяем, что debugTextEdit инициализирован
		{
			debugTextEdit->appendPlainText(localMsg.constData());
		}
		break;
	}
}

// check files
bool checkFilesExistence()
{
	QStringList filepaths;  // Создаем список для хранения путей к файлам
	filepaths << "data/CNST/gen0_CNST.ini"
		<< "data/CNST/gen1_CNST.ini"
		<< "data/CNST/gen2_CNST.ini"
		<< "data/CNST/NewEngineAS1_CNST.ini"
		<< "data/CNST/NewEngineAS2_CNST.ini"
		<< "data/OBJ/asworld_OBJ.ini"
		<< "data/OBJ/gen0_OBJ.ini"
		<< "data/OBJ/gen1.1_OBJ.ini"
		<< "data/OBJ/gen1_OBJ.ini"
		<< "data/OBJ/gen2_OBJ.ini"
		<< "data/OBJ/legend_OBJ.ini"
		<< "data/OBJ/zs1mobile_OBJ.ini"
		<< "data/OBJ/zs2_OBJ.ini"
		<< "data/SFX/extSFX.ini"
		<< "data/SFX/gen1.1_extSFX.ini"
		<< "data/SFX/non_extSFX.ini"
		<< "data/WEAP/CrazyLunch_WEAP.ini"
		<< "data/WEAP/gen0_WEAP.ini"
		<< "data/WEAP/gen1.1_WEAP.ini"
		<< "data/WEAP/gen1_WEAP.ini"
		<< "data/WEAP/gen2_WEAP.ini"
		<< "data/constants.ini";

	QStringList missingFiles;  // Создаем список для хранения отсутствующих файлов

	// Проверка наличия файлов
	for (const QString& filepath : filepaths)
	{
		if (!QFile::exists(filepath))
		{
			missingFiles << filepath;
		}
	}

	// Если есть отсутствующие файлы
	if (!missingFiles.isEmpty())
	{
		QString errorMessage = "The following files are missing:\n\n";
		errorMessage += missingFiles.join("\n") + "\n\n";
		errorMessage += "Please check your program installation. Make sure the required files are present.";

		QMessageBox::critical(nullptr, "Error", errorMessage);

		return false;
	}

	return true;
}

// browse button functional
void MainWindow::handleBrowseButtonClicked()
{
	QString gameFilesFilter = "Game Files (*.res *.db)";
	QString allFilesFilter = "All Files (*)";

	QStringList filters;
	filters << gameFilesFilter << allFilesFilter;

	ResFilename = QFileDialog::getOpenFileName(this, "Select File", QString(), filters.join(";;"));

	if (!ResFilename.isEmpty())
	{
		filenameLineEdit->setText(ResFilename);
	}
}

// unpack button functional
void MainWindow::handleUnpackButtonClicked()
{
	ResFilename = filenameLineEdit->text();
	QString mode = modeComboBox->currentText();

	// Проверяем, существует ли файл
	QFile file(ResFilename);
	bool fileExists = file.exists();

	if (!fileExists)
	{
		// Файл не найден, выводим сообщение об ошибке
		QMessageBox::critical(this, "Error", "File not selected!");
		return;
	}

	// Проверяем, существуют ли необходимые файлы
	if (!checkFilesExistence())
	{
		return;
	}

	// Проверяем, существует ли папка 'unpacked_inis'
	QString unpackedFolderFound = QDir::currentPath() + "/unpacked_inis";
	QDir dir(unpackedFolderFound);
	bool unpackedFolderExists = dir.exists();

	if (unpackedFolderExists)
	{
		// Папка 'unpacked_inis' существует, выводим предупреждение
		QMessageBox::StandardButton answer = QMessageBox::question(
			this,
			"Warning",
			"To avoid problems with unpacking, it is recommended to clear the previous results in the 'unpacked_inis' folder. Do you want to remove them?",
			QMessageBox::Yes | QMessageBox::No
		);

		if (answer == QMessageBox::Yes)
		{
			// Удаляем содержимое папки 'unpacked_inis'
			bool success = dir.removeRecursively();
			if (!success)
			{
				QMessageBox::critical(this, "Error", "Failed to clear the 'unpacked_inis' folder!");
				return;
			}
		}
		else
		{
			// Пользователь отказался удалять предыдущие результаты
			QMessageBox::information(this, "Information", "Unpacking canceled by user.");
			return;
		}
	}

	// Очистка окна дебага перед началом новой распаковки
	if (debugTextEdit != nullptr)
	{
		debugTextEdit->clear();
	}

	// Вывод информации в окно дебага
	debugTextEdit->appendPlainText("File: " + ResFilename);
	debugTextEdit->appendPlainText("Mode: " + mode);
	debugTextEdit->appendPlainText("Alternative Mode Enabled: " + QString(alternativeModeEnabled ? "Yes\n" : "No\n"));


	unpackButton->setText("Unpacking...");
	QCoreApplication::processEvents(); // Обновляем интерфейс для отображения нового текста

	FileUnpacker::processFileUnpackMode(ResFilename, modeComboBox->currentText(), alternativeModeEnabled); // Передаем функции имя файла, имя режима и данные о альтернативной распаковке

	unpackButton->setText("Unpack");

	// Оповещение о распаковке файла
	QString message = ::ResFilename + " has been unpacked into the 'unpacked_inis' folder.";
	QMessageBox::information(this, "Information", message, QMessageBox::Ok);
	// Открываем папку 'unpacked_inis'
	QString unpackedFolderPath = QDir::currentPath() + "/unpacked_inis";
	QDesktopServices::openUrl(QUrl::fromLocalFile(unpackedFolderPath));
}

// makeres button functional
void MainWindow::handleMakeResButtonClicked()
{
    debugTextEdit->clear();

    QString mode = packModeComboBox->currentText();

    qDebug() << "MakeRes mode:" << mode;

	QString workingDirectory = QCoreApplication::applicationDirPath();
	QString ini2resPath = workingDirectory + "/bin/ini2res.exe";
	QString ini2dbPath = workingDirectory + "/bin/ini2db.exe";

	// Проверяем наличие файлов ini2res и ini2db
	bool ini2resExists = QFile::exists(ini2resPath);
	bool ini2dbExists = QFile::exists(ini2dbPath);

	if ((mode == "AS/ZS Engine" && !ini2resExists) ||
		(mode == "Objects Extended Engine" && !ini2dbExists) ||
		(mode == "Locoland Engine" && !ini2resExists))
	{
		// Если файл ini2res или ini2db не найден, выводим предупреждение и блокируем кнопку
		QString errorMessage = "Compilation cancelled. Compilers not found. Please check the installation of the program.\n\n"
			"The following files are missing:\n\n";
		if (!ini2resExists)
			errorMessage += "bin/ini2res.exe\n";
		if (!ini2dbExists)
			errorMessage += "bin/ini2db.exe\n";

		QMessageBox::critical(this, "Res Compilation - Files Missing", errorMessage);
		return;
	}

	if (mode == "AS/ZS Engine")
	{
		QString workingDirectory = QCoreApplication::applicationDirPath();

		// Полный путь к ini2res
		QString ini2resPath = workingDirectory + "/bin/ini2res";

		// Полный путь к выходному файлу objects.res
		QString objectsResPath = workingDirectory + "/compiled_res/objects.res";

		// Удаляем папку compiled_res, если она существует
		QDir compiledResDir(workingDirectory + "/compiled_res");
		compiledResDir.removeRecursively();

		QStringList iniFiles = {
			"OBJ.ini",
			"WEAP.ini",
			"CNST.ini",
			"SFX.ini"
		};

		QStringList missingFiles; // Список недостающих файлов

		foreach(const QString & iniFile, iniFiles)
		{
			QString iniFilePath = workingDirectory + "/unpacked_inis/" + iniFile;

			// Проверяем наличие файла
			if (!QFile::exists(iniFilePath))
			{
				qDebug() << "File not found:" << iniFilePath;
				missingFiles.append(iniFile); // Добавляем недостающий файл в список
			}
		}

		if (missingFiles.isEmpty())
		{
			foreach(const QString & iniFile, iniFiles)
			{
				QString iniFilePath = workingDirectory + "/unpacked_inis/" + iniFile;

				// Создаем папку compiled_res
				QDir().mkpath(workingDirectory + "/compiled_res");

				// Запускаем процесс ini2res для каждого ini-файла
				QProcess process;
				process.setWorkingDirectory(workingDirectory);
				process.start(ini2resPath, QStringList() << iniFilePath << objectsResPath);
				process.waitForFinished(-1);

				qDebug() << "Compilation completed for file:" << iniFile;
			}

			// Оповещение и открытие папки
			QMessageBox::information(this, "Res Compilation", "Compilation completed.");
			QDesktopServices::openUrl(QUrl::fromLocalFile(workingDirectory + "/compiled_res"));
		}
		else
		{
			QString errorMessage = "The following files are missing:\n\n";
			foreach(const QString & missingFile, missingFiles)
			{
				QString missingFilePath = workingDirectory + "/unpacked_inis/" + missingFile;
				errorMessage += missingFile + " (Path: " + missingFilePath + ")\n";
			}
			errorMessage += "\nPlease ensure that all required files are unpacked before compiling.";
			QMessageBox::critical(this, "Res Compilation - Files Missing", errorMessage);
		}
	}

	else if (mode == "Objects Extended Engine")
	{
		QString workingDirectory = QCoreApplication::applicationDirPath();

		// Полный путь к ini2res
		QString ini2resPath = workingDirectory + "/bin/ini2db";

		// Полный путь к выходному файлу objects.res
		QString objectsResPath = workingDirectory + "/compiled_res/ObjectsExteneded.db";

		// Удаляем папку compiled_res, если она существует
		QDir compiledResDir(workingDirectory + "/compiled_res");
		compiledResDir.removeRecursively();

		QStringList iniFiles = {
			"CNST.ini",
			"WEAP.ini",
			"OBJ.ini",
			"SFX.ini"
		};

		QStringList missingFiles; // Список недостающих файлов

		foreach(const QString & iniFile, iniFiles)
		{
			QString iniFilePath = workingDirectory + "/unpacked_inis/" + iniFile;

			// Проверяем наличие файла
			if (!QFile::exists(iniFilePath))
			{
				qDebug() << "File not found:" << iniFilePath;
				missingFiles.append(iniFile); // Добавляем недостающий файл в список
			}
		}

		if (missingFiles.isEmpty())
		{
			foreach(const QString & iniFile, iniFiles)
			{
				QString iniFilePath = workingDirectory + "/unpacked_inis/" + iniFile;

				// Создаем папку compiled_res
				QDir().mkpath(workingDirectory + "/compiled_res");

				// Запускаем процесс ini2res для каждого ini-файла
				QProcess process;
				process.setWorkingDirectory(workingDirectory);
				process.start(ini2resPath, QStringList() << iniFilePath << objectsResPath);
				process.waitForFinished(-1);

				qDebug() << "Compilation completed for file:" << iniFile;
			}

			// Оповещение и открытие папки
			QMessageBox::information(this, "Res Compilation", "Compilation completed.");
			QDesktopServices::openUrl(QUrl::fromLocalFile(workingDirectory + "/compiled_res"));
		}
		else
		{
			QString errorMessage = "The following files are missing:\n\n";
			foreach(const QString & missingFile, missingFiles)
			{
				QString missingFilePath = workingDirectory + "/unpacked_inis/" + missingFile;
				errorMessage += missingFile + " (Path: " + missingFilePath + ")\n";
			}
			errorMessage += "\nPlease ensure that all required files are unpacked before compiling.";
			QMessageBox::critical(this, "Res Compilation - Files Missing", errorMessage);
		}
	}

	else if (mode == "Locoland Engine")
	{
		QString workingDirectory = QCoreApplication::applicationDirPath();

		// Полный путь к ini2res
		QString ini2resPath = workingDirectory + "/bin/ini2res";

		// Полный путь к выходному файлу objects.res
		QString objectsResPath = workingDirectory + "/compiled_res/Locoland.res";

		// Удаляем папку compiled_res, если она существует
		QDir compiledResDir(workingDirectory + "/compiled_res");
		compiledResDir.removeRecursively();

		QStringList iniFiles = {
			"OBJ.ini",
			"CNST.ini",
			"WEAP.ini",
			"SFX.ini"
		};

		QStringList missingFiles; // Список недостающих файлов

		foreach(const QString & iniFile, iniFiles)
		{
			QString iniFilePath = workingDirectory + "/unpacked_inis/" + iniFile;

			// Проверяем наличие файла
			if (!QFile::exists(iniFilePath))
			{
				qDebug() << "File not found:" << iniFilePath;
				missingFiles.append(iniFile); // Добавляем недостающий файл в список
			}
		}

		if (missingFiles.isEmpty())
		{
			foreach(const QString & iniFile, iniFiles)
			{
				QString iniFilePath = workingDirectory + "/unpacked_inis/" + iniFile;

				// Создаем папку compiled_res
				QDir().mkpath(workingDirectory + "/compiled_res");

				// Запускаем процесс ini2res для каждого ini-файла
				QProcess process;
				process.setWorkingDirectory(workingDirectory);
				process.start(ini2resPath, QStringList() << iniFilePath << objectsResPath);
				process.waitForFinished(-1);

				qDebug() << "Compilation completed for file:" << iniFile;
			}

			// Оповещение и открытие папки
			QMessageBox::information(this, "Res Compilation", "Compilation completed.");
			QDesktopServices::openUrl(QUrl::fromLocalFile(workingDirectory + "/compiled_res"));
		}
		else
		{
			QString errorMessage = "The following files are missing:\n\n";
			foreach(const QString & missingFile, missingFiles)
			{
				QString missingFilePath = workingDirectory + "/unpacked_inis/" + missingFile;
				errorMessage += missingFile + " (Path: " + missingFilePath + ")\n";
			}
			errorMessage += "\nPlease ensure that all required files are unpacked before compiling.";
			QMessageBox::critical(this, "Res Compilation - Files Missing", errorMessage);
		}
	}
    else
    {
        return;
    }
}

// Unpack description function
void MainWindow::handleModeComboBoxChanged(const QString& mode)
{
	QString description;

	if (mode == "as1_engine") {
		description = "Alien Shooter 1 (PC/Mobile)\n"
			"Alien Shooter 1 - Last Hope (PC/Mobile)\n"
			"Alien Shooter 1 - Lost World (Theseus Mobile)";
	}
	else if (mode == "theseus_pc") {
		description = "Theseus - Return of the Hero (PC Only)";
	}
	else if (mode == "as1world") {
		description = "Alien Shooter 1 - World";
	}
	else if (mode == "zs1") {
		description = "Zombie Shooter 1 (PC Only)";
	}
	else if (mode == "zs1_mobile") {
		description = "Zombie Shooter 1 (Mobile Only)";
	}
	else if (mode == "as2_original") {
		description = "Alien Shooter 2 (1.0/Gold/Vengeance)";
	}
	else if (mode == "as2_addons") {
		description = "Alien Shooter 2 - Reloaded\n"
			"Alien Shooter 2 - Conscription\n"
			"Zombie Shooter 2 - Teaser";
	}
	else if (mode == "zs2_engine") {
		description = "Zombie Shooter 2\n"
			"Alien Shooter - Revisited";
	}
	else if (mode == "as2legend_engine") {
		description = "Alien Shooter 2 - The Legend (PC/Mobile)\n"
			"Alien Shooter 2 - TD (PC/Mobile)\n"
			"Alien Shooter 2 - New Era\n"
			"Alien Shooter 2 - Reloaded (Mobile)";
	}
	else if (mode == "oe_engine") {
		description = "Objects Extended Project (version 1.1.0.6+)";
	}
	else if (mode == "crazylunch") {
		description = "Crazy Lunch";
	}
	else if (mode == "chackstemple") {
		description = "Chacks Temple";
	}
	else if (mode == "locoland") {
		description = "Locoland/Steamland";
	}

	debugTextEdit->clear();  // Очистить содержимое перед добавлением нового текста
	debugTextEdit->appendPlainText("Game support:\n" + description);

}

// MakeRes description function
void MainWindow::handlePackModeComboBoxChanged(const QString& mode)
{
	QString description;

	if (mode == "AS/ZS Engine") {
		description = "The compiler supports all Alien Shooter and Zombie Shooter games.";
	}
	else if (mode == "Objects Extended Engine") {
		description = "The compiler only supports the Objects Extended Project.";
	}
	else if (mode == "Locoland Engine") {
		description = "The compiler only supports the Locoland/Steamland.";
	}

	debugTextEdit->clear();  // Очистить содержимое перед добавлением нового текста
	debugTextEdit->appendPlainText("Compiler support:\n" + description);

}