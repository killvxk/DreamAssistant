#ifndef TU_EDITBUTTON_H
#define TU_EDITBUTTON_H

#include <QPushButton>

class QLineEdit;

class EditButton : public QPushButton
{
	Q_OBJECT
public:
	EditButton(QLineEdit *edit);
};

#endif // TU_EDITBUTTON_H
