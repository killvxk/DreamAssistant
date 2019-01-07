#ifndef TU_UTILS_H
#define TU_UTILS_H

#include <QString>

#define ITEMHEIGHT 30
#define ITEMHSPACE 10
#define ITEMVSPACE 5
#define PAGESPACE  20
#define ITEMWIDTH  650

#define DEFAULT_SKIN                     (":/res/skin/default/4.png")

#define DREAM_COMPANY_SETTING            ("DreamAssistant")
#define DREAM_SETTING_FILE_NAME_SETTING  ("DreamAssistant")

typedef enum {
	DREAM_EN,
	DREAM_ZH_CN,
	DREAM_ES,
} LANGUAGE;

struct AutoData {
	QString appPath;
	QString appName;
	QString appComment;
	QString iconName;
	QString appStatus;
};

typedef enum {
	BUTTON_ENTER,
	BUTTON_LEAVE,
	BUTTON_PRESSED,
	BUTTON_DISABLE,
	BUTTON_FIRST,
	BUTTON_SCALED,
} BUTTONSTATUS;

typedef enum {
	HOMEPAGE,
	CLEANUPPAGE,
	EVALUATIONPAGE,
	FEATUREPAGE,
	TOOLKITSPAGE,
} PAGESTATUS;

#endif // TU_UTILS_H
