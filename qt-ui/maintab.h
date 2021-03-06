/*
 * maintab.h
 *
 * header file for the main tab of Subsurface
 *
 */
#ifndef MAINTAB_H
#define MAINTAB_H

#include <QTabWidget>
#include <QDialog>
#include <QMap>
#include <QUuid>

#include "ui_maintab.h"
#include "completionmodels.h"
#include "dive.h"

class WeightModel;
class CylindersModel;
class ExtraDataModel;
class QCompleter;

struct Completers {
	QCompleter *location;
	QCompleter *divemaster;
	QCompleter *buddy;
	QCompleter *suit;
	QCompleter *tags;
};

class MainTab : public QTabWidget {
	Q_OBJECT
public:
	enum EditMode {
		NONE,
		DIVE,
		TRIP,
		ADD,
		MANUALLY_ADDED_DIVE,
		IGNORE
	};

	MainTab(QWidget *parent = 0);
	~MainTab();
	void clearStats();
	void clearInfo();
	void clearEquipment();
	void reload();
	void initialUiSetup();
	bool isEditing();
	void updateCoordinatesText(qreal lat, qreal lon);
	void nextInputField(QKeyEvent *event);
	void showAndTriggerEditSelective(struct dive_components what);

signals:
	void addDiveFinished();
	void dateTimeChanged();
	void requestDiveSiteEdit(uint32_t uuid);
public
slots:
	void addCylinder_clicked();
	void addWeight_clicked();
	void updateDiveInfo(bool clear = false);
	void acceptChanges();
	void rejectChanges();
	void on_location_textChanged(const QString &text);
	void on_location_editingFinished();
	void on_divemaster_textChanged();
	void on_buddy_textChanged();
	void on_suit_textChanged(const QString &text);
	void on_notes_textChanged();
	void on_airtemp_textChanged(const QString &text);
	void divetype_Changed(int);
	void on_watertemp_textChanged(const QString &text);
	void validate_temp_field(QLineEdit *tempField, const QString &text);
	void on_dateEdit_dateChanged(const QDate &date);
	void on_timeEdit_timeChanged(const QTime & time);
	void on_rating_valueChanged(int value);
	void on_visibility_valueChanged(int value);
	void on_tagWidget_textChanged();
	void editCylinderWidget(const QModelIndex &index);
	void editWeightWidget(const QModelIndex &index);
	void addDiveStarted();
	void addMessageAction(QAction *action);
	void hideMessage();
	void closeMessage();
	void displayMessage(QString str);
	void enableEdition(EditMode newEditMode = NONE);
	void toggleTriggeredColumn();
	void updateTextLabels(bool showUnits = true);
	void escDetected(void);
	void photoDoubleClicked(const QString filePath);
	void removeSelectedPhotos();
	void prepareDiveSiteEdit();
	void showLocation();

private:
	Ui::MainTab ui;
	WeightModel *weightModel;
	CylindersModel *cylindersModel;
	ExtraDataModel *extraDataModel;
	EditMode editMode;
	BuddyCompletionModel buddyModel;
	DiveMasterCompletionModel diveMasterModel;
	LocationCompletionModel locationModel;
	SuitCompletionModel suitModel;
	TagCompletionModel tagModel;
	DivePictureModel *divePictureModel;
	Completers completers;
	bool modified;
	bool copyPaste;
	void resetPallete();
	void saveTags();
	void saveTaggedStrings();
	void diffTaggedStrings(QString currentString, QString displayedString, QStringList &addedList, QStringList &removedList);
	void markChangedWidget(QWidget *w);
	dive_trip_t *currentTrip;
	dive_trip_t displayedTrip;
	bool acceptingEdit;
};

#endif // MAINTAB_H
