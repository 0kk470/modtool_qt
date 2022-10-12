#ifndef OVERLAYWIDGET_H
#define OVERLAYWIDGET_H

#include <QtGui>
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#include <QtWidgets>
#endif

class OverlayWidget : public QWidget {
   void newParent() {
      if (!parent()) return;
      parent()->installEventFilter(this);
      raise();
   }
public:
   explicit OverlayWidget(QWidget *parent = {}) : QWidget(parent) {
      setAttribute(Qt::WA_NoSystemBackground);
      //setAttribute(Qt::WA_TransparentForMouseEvents);
      newParent();
   }
protected:
   //! Catches resize and child events from the parent widget
   bool eventFilter(QObject *obj, QEvent *ev) override {
      if (obj == parent()) {
         if (ev->type() == QEvent::Resize)
            resize(static_cast<QResizeEvent*>(ev)->size());
         else if (ev->type() == QEvent::ChildAdded)
            raise();
      }
      return QObject::eventFilter(obj, ev);
   }

   //! Tracks parent widget changes
   bool event(QEvent *ev) override {
      if (ev->type() == QEvent::ParentAboutToChange) {
         if (parent()) parent()->removeEventFilter(this);
      }
      else if (ev->type() == QEvent::ParentChange)
         newParent();
      return QWidget::event(ev);
   }

};

class LoadingOverlay : public OverlayWidget
{
public:
   LoadingOverlay(QWidget *parent = {}) : OverlayWidget{parent} {
      setAttribute(Qt::WA_NoMousePropagation);
      setStyleSheet("background-color:rgba(255, 255, 255, 110);");
      QVBoxLayout *verticalLayout = new QVBoxLayout(this);
      m_LoadLabel = new QLabel(this);
      m_LoadLabel->setAlignment(Qt::AlignCenter);
      m_LoadLabel->setStyleSheet("color:rgb(255,255,255);\nfont: 87 9pt 'Arial Black';");
      verticalLayout->addWidget(m_LoadLabel);
   }

   void DisplayNewText(const QString& msg)
   {
       show();
       m_LoadLabel->setText(msg);
   }

   void DisplayNextLine(const QString& msg)
   {
       show();
       auto curText = m_LoadLabel->text();
       curText += "\n" + msg;
       m_LoadLabel->setText(msg);
   }

private:
    QLabel* m_LoadLabel;

protected:
    void hideEvent(QHideEvent * event) override
    {
        m_LoadLabel->setText("");
        OverlayWidget::hideEvent(event);
    }

};


#endif // OVERLAYWIDGET_H
