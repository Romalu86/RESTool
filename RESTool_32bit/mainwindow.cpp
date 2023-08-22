// Testing Build

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Functions/file_modes.h"
#include <QProcess>
#include <QTemporaryDir>
#include <QDesktopServices>
#include <QMenuBar>
#include <QStyleFactory>
#include <QDebug>

QString ResFilename; // инициализация переменной для проверки файла
QPlainTextEdit* MainWindow::debugTextEdit = nullptr; // Инициализация статической переменной debugTextEdit

// UI interface intialization
MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent), ui(new Ui::MainWindow) // Инициализация объекта ui
{
	ui->setupUi(this); // Настройка пользовательского интерфейса
	setFixedSize(546, 648); // Установка фиксированного размера окна

	QApplication::setStyle(QStyleFactory::create("Fusion")); // Ставим тему Fusion по умолчанию

	// Создание меню приложения
	appMenuBar = new QMenuBar(this);

	// Создание пункта "Menu"
	QMenu* fileMenu = appMenuBar->addMenu("Menu");

	// Создание пункта меню "Open File" в меню "Menu"
	openFileAction = fileMenu->addAction("Open File");
	openFileAction->setIcon(QIcon(":/resources/file_open.png"));
	connect(openFileAction, &QAction::triggered, this, &MainWindow::handleBrowseButtonClicked);

	// Создание пункта меню "Analyze File" в меню "Menu"
	analyzeFileAction = fileMenu->addAction("Analyze File");
	analyzeFileAction->setIcon(QIcon(":/resources/file_analyze.png"));
	connect(analyzeFileAction, &QAction::triggered, this, &MainWindow::handleAnalyzeButtonClicked);

	// Создание пункта меню "Convert VID" в меню "Menu"
	VidConvertAction = fileMenu->addAction("Convert VID");
	VidConvertAction->setIcon(QIcon(":/resources/convert_vid.png"));
	connect(VidConvertAction, &QAction::triggered, this, &MainWindow::handleConvertVidButtonClicked);

	fileMenu->addSeparator();

	// Создание меню "Themes" в меню "Menu"
	QMenu* themesMenu = fileMenu->addMenu("Themes");
	themesMenu->setIcon(QIcon(":/resources/themes.png"));

	// Создание пунктов меню "Fusion", "Windows" в меню "Themes"
	fusionThemeAction = themesMenu->addAction("Fusion");
	windowsThemeAction = themesMenu->addAction("Windows");
	fusionThemeAction->setIcon(QIcon(":/resources/qt.png"));
	windowsThemeAction->setIcon(QIcon(":/resources/qt.png"));

	// Связывание пунктов меню с функцией изменения темы приложения
	connect(fusionThemeAction, &QAction::triggered, this, &MainWindow::changeThemeToFusion);
	connect(windowsThemeAction, &QAction::triggered, this, &MainWindow::changeThemeToWindows);

	// Создание пункта меню "Exit" в меню "File"
	QAction* exitAction = fileMenu->addAction("Exit");
	exitAction->setIcon(QIcon(":/resources/exit.png"));
	connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

	// Создание пункта "Links"
	QMenu* linksMenu = appMenuBar->addMenu("Links");

	// Создание пунктов меню в меню "Links"
	OEProjectLink = linksMenu->addAction("Objects Extended Project (ModDB)");
	VKLink = linksMenu->addAction("VK.com (Modding Group)");

	VKLink->setIcon(QIcon(":/resources/vk.png"));
	OEProjectLink->setIcon(QIcon(":/resources/mod.png"));

	connect(VKLink, &QAction::triggered, this, &MainWindow::openVKLink);
	connect(OEProjectLink, &QAction::triggered, this, &MainWindow::openOELink);

	// Установка меню приложения в качестве меню окна
	setMenuBar(appMenuBar);

	// Получение указателей на виджеты из загруженного .ui файла
	filenameLineEdit = findChild<QLineEdit*>("filenameLineEdit");
	browseButton = findChild<QPushButton*>("browseButton");
	modeComboBox = findChild<QComboBox*>("modeComboBox");
	unpackButton = findChild<QPushButton*>("unpackButton");
	packModeComboBox = findChild<QComboBox*>("packModeComboBox");
	makeResButton = findChild<QPushButton*>("makeResButton");
	debugTextEdit = findChild<QPlainTextEdit*>("debugTextEdit");
	checkBox = findChild<QCheckBox*>("checkBox");
	AnalyzeButton = findChild<QPushButton*>("AnalyzeButton");
	LastNVidlineEdit = findChild<QLineEdit*>("LastNVidlineEdit");
	FirstNVidlineEdit = findChild<QLineEdit*>("FirstNVidlineEdit");
	VIDmodeComboBox = findChild<QComboBox*>("VIDmodeComboBox");
	OpenVIDButton = findChild<QPushButton*>("OpenVIDButton");
	ConvertVIDButton = findChild<QPushButton*>("ConvertVIDButton");

	// принудительно ставим режим чтобы показать его описание при первом запуске
	modeComboBox->setCurrentText("Alien Shooter 1 Engine");
	handleModeComboBoxChanged("Alien Shooter 1 Engine");
	// список режимов распаковки
	modeComboBox->addItem("Alien Shooter 1 Engine");
	modeComboBox->addItem("Alien Shooter 1 - World Engine");
	modeComboBox->addItem("Alien Shooter 2 - Addons Engine");
	modeComboBox->addItem("Alien Shooter 2 - Original Engine");
	modeComboBox->addItem("Alien Shooter 2 - Updated Engine");
	modeComboBox->addItem("Crazy Lunch Engine");
	modeComboBox->addItem("Chacks Temple Engine");
	modeComboBox->addItem("Locoland Engine");
	modeComboBox->addItem("Objects Extended Engine");
	modeComboBox->addItem("Theseus (PC Version Engine)");
	modeComboBox->addItem("Zombie Shooter 1 Engine");
	modeComboBox->addItem("Zombie Shooter 1 - Mobile Engine");
	modeComboBox->addItem("Zombie Shooter 2 Engine");
	// список режимов упаковки
	packModeComboBox->addItem("AS/ZS Engine");
	packModeComboBox->addItem("Locoland Engine");
	packModeComboBox->addItem("Objects Extended Engine");
	// список режимов открытия VID
	VIDmodeComboBox->addItem("AS1/ZS1 Engine");
	VIDmodeComboBox->addItem("AS2/ZS2 Engine");

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
	connect(VIDmodeComboBox, QOverload<const QString&>::of(&QComboBox::currentTextChanged), this, &MainWindow::handleVIDmodeComboBoxChanged);
	connect(makeResButton, &QPushButton::clicked, this, &MainWindow::handleMakeResButtonClicked);
	connect(checkBox, &QCheckBox::stateChanged, this, &MainWindow::handleCheckBoxStateChanged);
	connect(AnalyzeButton, &QPushButton::clicked, this, &MainWindow::handleAnalyzeButtonClicked);
	connect(OpenVIDButton, &QPushButton::clicked, this, &MainWindow::handleOpenVidButtonClicked);
	connect(ConvertVIDButton, &QPushButton::clicked, this, &MainWindow::handleConvertVidButtonClicked);

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
		alternativeModeEnabled = false; // устраняем баг с активацией режима когда галочка не выставлена.
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
			"To avoid problems with unpacking, it is necessary to clear the previous results in the 'unpacked_inis' folder. Do you want to remove them?",
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
	debugTextEdit->appendPlainText("Alternative Mode: " + QString(alternativeModeEnabled ? "Enabled\n" : "Disabled\n"));


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

	qDebug() << "MakeRes mode: " << mode << "\n";

	// Получаем текущий рабочий каталог программы
	QString workingDirectory = QCoreApplication::applicationDirPath();

	// Создаем временную директорию
	QTemporaryDir tempDir;

	if (!tempDir.isValid())
	{
		QMessageBox::critical(this, "Error", "Failed to create temporary directory.");
		return;
	}

	// Копируем ini2res.exe во временную директорию
	QString ini2resPath = tempDir.path() + "/ini2res.exe";
	if (!QFile::copy(":/resources/bin/ini2res.exe", ini2resPath))
	{
		QMessageBox::critical(this, "Error", "Failed to copy ini2res.exe to temporary directory.");
		return;
	}

	// Копируем ini2db.exe во временную директорию
	QString ini2dbPath = tempDir.path() + "/ini2db.exe";
	if (!QFile::copy(":/resources/bin/ini2db.exe", ini2dbPath))
	{
		QMessageBox::critical(this, "Error", "Failed to copy ini2db.exe to temporary directory.");
		return;
	}

	if (mode == "AS/ZS Engine")
	{
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
				process.setWorkingDirectory(tempDir.path()); // Здесь используем временную директорию

				// Перенаправляем стандартный вывод и стандартный поток ошибок на устройство null
				process.setStandardOutputFile(QProcess::nullDevice());
				process.setStandardErrorFile(QProcess::nullDevice());

				// Запускаем процесс асинхронно
				process.start(ini2resPath, QStringList() << iniFilePath << objectsResPath);

				// Ждем, когда процесс завершится, но не блокируем пользовательский интерфейс
				while (!process.waitForFinished(100))
				{
					// Продолжаем обработку событий пользовательского интерфейса
					QCoreApplication::processEvents();
				}

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
		QString objectsResPath = workingDirectory + "/compiled_res/ObjectsExtended.db";
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

				// Запускаем процесс ini2db для каждого ini-файла
				QProcess process;
				process.setWorkingDirectory(tempDir.path()); // Здесь используем временную директорию

				// Перенаправляем стандартный вывод и стандартный поток ошибок на устройство null
				process.setStandardOutputFile(QProcess::nullDevice());
				process.setStandardErrorFile(QProcess::nullDevice());

				// Запускаем процесс асинхронно
				process.start(ini2dbPath, QStringList() << iniFilePath << objectsResPath);

				// Ждем, когда процесс завершится, но не блокируем пользовательский интерфейс
				while (!process.waitForFinished(100))
				{
					// Продолжаем обработку событий пользовательского интерфейса
					QCoreApplication::processEvents();
				}

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

	// Обработка режима "Locoland Engine"
	else if (mode == "Locoland Engine")
	{
		QString objectsResPath = workingDirectory + "/compiled_res/Locoland.res";
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
				process.setWorkingDirectory(tempDir.path()); // Здесь используем временную директорию

				// Перенаправляем стандартный вывод и стандартный поток ошибок на устройство null
				process.setStandardOutputFile(QProcess::nullDevice());
				process.setStandardErrorFile(QProcess::nullDevice());

				// Запускаем процесс асинхронно
				process.start(ini2resPath, QStringList() << iniFilePath << objectsResPath);

				// Ждем, когда процесс завершится, но не блокируем пользовательский интерфейс
				while (!process.waitForFinished(100))
				{
					// Продолжаем обработку событий пользовательского интерфейса
					QCoreApplication::processEvents();
				}

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

	if (mode == "Alien Shooter 1 Engine") {
		description = "Alien Shooter 1 (PC/Mobile)\n"
			"Alien Shooter 1 - Last Hope (PC/Mobile)\n"
			"Alien Shooter 1 - Lost World (Theseus Mobile)";
	}
	else if (mode == "Theseus (PC Version Engine)") {
		description = "Theseus - Return of the Hero (PC Only)";
	}
	else if (mode == "Alien Shooter 1 - World Engine") {
		description = "Alien Shooter 1 - World (Free)";
	}
	else if (mode == "Zombie Shooter 1 Engine") {
		description = "Zombie Shooter 1 (PC Only)";
	}
	else if (mode == "Zombie Shooter 1 - Mobile Engine") {
		description = "Zombie Shooter 1 (Mobile Only)";
	}
	else if (mode == "Alien Shooter 2 - Original Engine") {
		description = "Alien Shooter 2 (1.0/Gold/Vengeance)";
	}
	else if (mode == "Alien Shooter 2 - Addons Engine") {
		description = "Alien Shooter 2 - Reloaded\n"
			"Alien Shooter 2 - Conscription\n"
			"Zombie Shooter 2 - Teaser";
	}
	else if (mode == "Alien Shooter 2 - Updated Engine") {
		description = "Alien Shooter 2 - The Legend (PC/Mobile)\n"
			"Alien Shooter 2 - TD (PC/Mobile)\n"
			"Alien Shooter 2 - New Era\n"
			"Alien Shooter 2 - Reloaded (Mobile)";
	}
	else if (mode == "Zombie Shooter 2 Engine") {
		description = "Zombie Shooter 2\n"
			"Alien Shooter - Revisited";
	}
	else if (mode == "Objects Extended Engine") {
		description = "Objects Extended Project (version 1.1.0.6+)";
	}
	else if (mode == "Crazy Lunch Engine") {
		description = "Crazy Lunch";
	}
	else if (mode == "Chacks Temple Engine") {
		description = "Chacks Temple";
	}
	else if (mode == "Locoland Engine") {
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
		description = "The compiler supports all Alien Shooter and Zombie Shooter games, including Theseus, Chacks Temple and Crazy Lunch.";
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

// VID description function
void MainWindow::handleVIDmodeComboBoxChanged(const QString& mode)
{
	QString description;

	if (mode == "AS1/ZS1 Engine") {
		description = "The viewer supports all games based on Alien Shooter 1 and Zombie Shooter 1 game engines.";
	}
	else if (mode == "AS2/ZS2 Engine") {
		description = "The viewer supports all games based on Alien Shooter 2 and Zombie Shooter 2 game engines.";
	}

	debugTextEdit->clear();  // Очистить содержимое перед добавлением нового текста
	debugTextEdit->appendPlainText("Vid viewer support:\n" + description);

}

// AnalyzeButton functional
void MainWindow::handleAnalyzeButtonClicked()
{

	QString filePath = QFileDialog::getOpenFileName(this, tr("Open OBJ.ini File"), QDir::homePath(), tr("INI Files (*.ini);;All Files (*)"));
	if (filePath.isEmpty()) {
		return;
	}
	debugTextEdit->clear();
	analyzeOBJIni(filePath);
}

// OBJ.ini analysis function
void MainWindow::analyzeOBJIni(const QString& filePath)
{
	// Получаем значения MIN_NVID, MAX_NVID, и MAX_ENTRIES_PER_LINE из пользовательского ввода
	bool conversionOk;
	int MIN_NVID = FirstNVidlineEdit->text().toInt(&conversionOk);
	if (!conversionOk)
	{
		debugTextEdit->appendPlainText("Error: Invalid value for 'First NVid'.");
		return;
	}

	int MAX_NVID = LastNVidlineEdit->text().toInt(&conversionOk);
	if (!conversionOk)
	{
		debugTextEdit->appendPlainText("Error: Invalid value for 'Last NVid'.");
		return;
	}

	int MAX_ENTRIES_PER_LINE = 6;

	// Открываем файл OBJ.ini
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		debugTextEdit->appendPlainText("Error opening the file.");
		return;
	}

	std::vector<int> nvidValues; // Вектор для хранения найденных значений NVid=

	QTextStream in(&file);
	while (!in.atEnd())
	{
		QString line = in.readLine();
		if (line.startsWith("NVid=")) // Проверяем, что строка начинается с "NVid="
		{
			int nvid = line.mid(5).toInt(&conversionOk); // Извлекаем значение NVid
			if (conversionOk)
			{
				if (nvid >= MIN_NVID && nvid <= MAX_NVID)
				{
					nvidValues.push_back(nvid);
				}
			}
			else
			{
				debugTextEdit->appendPlainText("Error: Invalid NVid value in OBJ.ini.");
			}
		}
	}

	file.close();

	// Сортируем вектор
	std::sort(nvidValues.begin(), nvidValues.end());

	// Очищаем содержимое debugTextEdit перед выводом результатов
	debugTextEdit->clear();

	if (nvidValues.empty()) {
		debugTextEdit->appendPlainText("No data for the NVid parameter.");
	}
	else {
		debugTextEdit->appendPlainText("Used NVid values:\n");

		int entriesInLine = 0;
		for (size_t i = 0; i < nvidValues.size(); ++i) {
			int start = nvidValues[i];
			while (i + 1 < nvidValues.size() && nvidValues[i + 1] == nvidValues[i] + 1) {
				i++;
			}
			int end = nvidValues[i];

			if (start == end) {
				debugTextEdit->insertPlainText(QString::number(start) + ", ");
			}
			else {
				debugTextEdit->insertPlainText(QString::number(start) + "-" + QString::number(end) + ", ");
			}

			entriesInLine++;
			if (entriesInLine >= MAX_ENTRIES_PER_LINE) {
				debugTextEdit->appendPlainText("");
				entriesInLine = 0;
			}
		}

		debugTextEdit->appendPlainText("\nFree NVid values:\n");

		entriesInLine = 0;
		int prevValue = MIN_NVID;
		for (const int nvid : nvidValues) {
			if (nvid > prevValue + 1) {
				if (prevValue == nvid - 2) {
					debugTextEdit->insertPlainText(QString::number(prevValue + 1) + ", ");
				}
				else {
					debugTextEdit->insertPlainText(QString::number(prevValue + 1) + "-" + QString::number(nvid - 1) + ", ");
				}
				entriesInLine++;
				if (entriesInLine >= MAX_ENTRIES_PER_LINE) {
					debugTextEdit->appendPlainText("");
					entriesInLine = 0;
				}
			}
			prevValue = nvid;
		}

		if (prevValue < MAX_NVID) {
			if (prevValue == MAX_NVID - 1) {
				debugTextEdit->insertPlainText(QString::number(prevValue + 1) + ", ");
			}
			else {
				debugTextEdit->insertPlainText(QString::number(prevValue + 1) + "-" + QString::number(MAX_NVID) + ", ");
			}
			entriesInLine++;
			if (entriesInLine >= MAX_ENTRIES_PER_LINE) {
				debugTextEdit->appendPlainText("");
			}
		}

		debugTextEdit->appendPlainText("");
		debugTextEdit->appendPlainText("Total free: " + QString::number((MAX_NVID + 1) - nvidValues.size()));
		debugTextEdit->appendPlainText("Total used: " + QString::number(nvidValues.size()));
	}
}

// Open VID File function
void MainWindow::handleOpenVidButtonClicked()
{
	QString selectedMode = VIDmodeComboBox->currentText();
	QString filePath = QFileDialog::getOpenFileName(this, "Open Vid File", "", "Vid Files (*.vid)");

	if (!filePath.isEmpty())
	{
		QString exePath;
		if (selectedMode == "AS1/ZS1 Engine")
		{
			exePath = ":/resources/bin/as1_vidview.exe";
		}
		else if (selectedMode == "AS2/ZS2 Engine")
		{
			exePath = ":/resources/bin/as2_vidview.exe";
		}
		else
		{
			// Handle unknown mode or error
			return;
		}

		QTemporaryDir tempDir;
		if (!tempDir.isValid())
		{
			qWarning() << "Failed to create temporary directory.";
			return;
		}

		QString tempExePath = tempDir.filePath("vidview.exe");
		QString tempFilePath = tempDir.filePath("input.vid");

		if (QFile::copy(exePath, tempExePath))
		{
			QFile::copy(filePath, tempFilePath);

			QProcess process;
			process.setWorkingDirectory(tempDir.path());  // Устанавливаем рабочую директорию

			QStringList arguments;
			arguments << "input.vid";  // Передаем имя файла без пути

			process.start(tempExePath, arguments);
			process.waitForFinished(-1);
		}
	}
}

// Convert VID File function
void MainWindow::handleConvertVidButtonClicked()
{
	QString filePath = QFileDialog::getOpenFileName(this, "Open Vid File", "", "Vid Files (*.vid)");

	if (!filePath.isEmpty())
	{
		QFileInfo fileInfo(filePath);
		QString originalFileName = fileInfo.fileName();

		QTemporaryDir tempDir;
		if (!tempDir.isValid())
		{
			qWarning() << "Failed to create temporary directory.";
			return;
		}

		QString tempExePath = tempDir.filePath("vidview.exe");
		QString tempFilePath = tempDir.filePath(originalFileName);

		QString exePath = ":/resources/bin/as2_vidview.exe";

		if (QFile::copy(exePath, tempExePath))
		{
			QFile::copy(filePath, tempFilePath);

			QProcess process;
			process.setWorkingDirectory(tempDir.path());

			QStringList arguments;
			arguments << "/c" << originalFileName;

			process.start(tempExePath, arguments);
			process.waitForFinished(-1);

			// Копируем файл в папку converted_vids в директории программы
			QString targetDir = QCoreApplication::applicationDirPath() + "/converted_vids/";
			QDir().mkpath(targetDir);
			QString targetFilePath = targetDir + originalFileName;

			// Удаляем существующий файл, если он есть
			if (QFile::exists(targetFilePath))
			{
				QFile::remove(targetFilePath);
			}

			QFile::copy(tempFilePath, targetFilePath);

			// Выводим оповещение
			QMessageBox::information(this, "Success", "File successfully converted and saved.");

			// Открываем папку converted_vids
			QDesktopServices::openUrl(QUrl::fromLocalFile(targetDir));
		}
	}
}

// Themes & Links
void MainWindow::changeThemeToFusion()
{
	QApplication::setStyle("fusion");
}

void MainWindow::changeThemeToWindows()
{
	QApplication::setStyle("windows");
}

void MainWindow::openVKLink()
{
	QDesktopServices::openUrl(QUrl("https://vk.com/as2modmaker"));
}

void MainWindow::openOELink()
{
	QDesktopServices::openUrl(QUrl("https://www.moddb.com/mods/objects-extended-project"));
}