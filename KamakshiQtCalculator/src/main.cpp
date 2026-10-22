#include <QtWidgets>
#include <cmath>
#include <functional>

static QString fmt(double x) {
    if (!std::isfinite(x)) return "Undefined";
    return QString::number(x, 'g', 12);
}

class SmartCalculator : public QMainWindow {
    Q_OBJECT
public:
    SmartCalculator() {
        setWindowTitle("kamakshi joshi | All-in-One Smart Calculator");
        resize(1160, 790);
        setMinimumSize(940, 650);
        auto *central = new QWidget;
        auto *root = new QVBoxLayout(central);
        root->setContentsMargins(20, 18, 20, 18);
        root->setSpacing(12);

        auto *header = new QFrame;
        header->setObjectName("header");
        auto *hh = new QHBoxLayout(header);
        auto *titleCol = new QVBoxLayout;
        auto *name = new QLabel("kamakshi joshi");
        name->setObjectName("brand");
        auto *sub = new QLabel("SMART CALCULATOR  •  SCIENCE  •  CONVERSIONS  •  INFORMATION / ENTROPY");
        sub->setObjectName("sub");
        titleCol->addWidget(name); titleCol->addWidget(sub);
        hh->addLayout(titleCol); hh->addStretch();
        auto *badge = new QLabel("C++  /  QT 6");
        badge->setObjectName("badge"); hh->addWidget(badge);
        root->addWidget(header);

        auto *body = new QHBoxLayout;
        body->setSpacing(14);
        auto *left = new QFrame; left->setObjectName("panel");
        left->setMinimumWidth(330); left->setMaximumWidth(410);
        auto *ll = new QVBoxLayout(left); ll->setContentsMargins(16,16,16,16); ll->setSpacing(10);
        auto *calcTitle = new QLabel("CALCULATOR"); calcTitle->setObjectName("section");
        ll->addWidget(calcTitle);
        expression = new QLineEdit;
        expression->setObjectName("expression");
        expression->setPlaceholderText("Enter expression or choose a tool →");
        expression->setMinimumHeight(48);
        ll->addWidget(expression);
        display = new QLabel("0"); display->setObjectName("display");
        display->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        display->setMinimumHeight(78); ll->addWidget(display);
        auto *grid = new QGridLayout; grid->setSpacing(7);
        QStringList keys={"7","8","9","÷","C","4","5","6","×","⌫","1","2","3","−","(", "0",".","=","+ ",")","sqrt","sin","cos","tan","^","log","ln","π","Ans","More"};
        int r=0,c=0;
        for (QString k:keys) {
            QString label=k.trimmed();
            auto *b=new QPushButton(label);
            if(label=="=") b->setObjectName("primary");
            else if(QStringList{"sqrt","sin","cos","tan","log","ln","More"}.contains(label)) b->setObjectName("cyan");
            grid->addWidget(b,r,c++);
            if(c==5){c=0;++r;}
            connect(b,&QPushButton::clicked,this,[=]{
                if(label=="C"){expression->clear();display->setText("0");return;}
                if(label=="⌫"){expression->backspace();return;}
                if(label=="="){lastAnswer=evaluate(expression->text());display->setText(lastAnswer);return;}
                if(label=="More"){tools->setCurrentIndex(0);return;}
                QString s=label;
                if(s=="×")s="*"; if(s=="÷")s="/"; if(s=="−")s="-";
                if(s=="sqrt")s="sqrt("; if(QStringList{"sin","cos","tan","log","ln"}.contains(s))s+="(";
                if(s=="π")s=QString::number(M_PI,'g',12);
                if(s=="Ans")s=lastAnswer;
                expression->insert(s);
            });
        }
        ll->addLayout(grid);
        auto *hint=new QLabel("Degrees for trig functions. Use expressions like sin(30), sqrt(81), 2^8, log(100).");
        hint->setObjectName("hint");hint->setWordWrap(true);ll->addWidget(hint);
        ll->addStretch();

        auto *right = new QFrame; right->setObjectName("panel");
        auto *rl = new QVBoxLayout(right); rl->setContentsMargins(14,14,14,14);
        auto *toolsTitle = new QLabel("ALL FEATURES"); toolsTitle->setObjectName("section");rl->addWidget(toolsTitle);
        tools = new QTabWidget; tools->setObjectName("tools");
        tools->addTab(infoTool(),"Unit Conversion");
        tools->addTab(entropyTool(),"Information (Bits/Nats/Decits)");
        tools->addTab(shannonEntropyTool(),"Entropy");
        tools->addTab(numberTool(),"Number systems");
        tools->addTab(efficiencyTool(),"Efficiency");
        tools->addTab(formulaTool(),"Formula lab");
        tools->addTab(currencyTool(),"Currency");
        rl->addWidget(tools,1);
        body->addWidget(left,0);body->addWidget(right,1);root->addLayout(body,1);
        auto *footer=new QLabel("DESIGNED FOR YOUR IDEAS  •  C++ / Qt 6  •  KAMAKSHI JOSHI");
        footer->setObjectName("footer");footer->setAlignment(Qt::AlignCenter);root->addWidget(footer);
        setCentralWidget(central);
        setStyleSheet(R"(
            QMainWindow,QWidget{background:#0b1020;color:#f5f3ff;font-family:'Segoe UI';font-size:13px}
            QFrame#header{background:qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 #7c3aed,stop:0.48 #2563eb,stop:1 #06b6d4);border:1px solid #8b5cf6;border-radius:20px}
            QLabel#brand{font-size:31px;font-weight:900;color:white;padding:2px}
            QLabel#sub{font-size:10px;font-weight:700;color:#ecfeff;letter-spacing:1px}
            QLabel#badge{font-weight:900;color:white;padding:12px;border:1px solid #a5f3fc;border-radius:10px;background:rgba(7,16,40,65)}
            QFrame#panel{background:#131b31;border:1px solid #35466c;border-radius:17px}
            QLabel#section{font-size:16px;font-weight:900;color:#c4b5fd;padding:5px;border-bottom:2px solid #7c3aed;background:#18213a}
            QLabel#display{background:#070d1b;border:1px solid #4f46e5;border-radius:13px;color:#5eead4;font-size:30px;font-weight:900;padding:13px}
            QLineEdit,QDoubleSpinBox,QComboBox,QPlainTextEdit{background:#0b1327;border:1px solid #40517a;border-radius:10px;padding:10px;color:#f8fafc;selection-background-color:#7c3aed;min-height:20px}
            QLineEdit:focus,QDoubleSpinBox:focus,QComboBox:focus,QPlainTextEdit:focus{border:2px solid #22d3ee}
            QPushButton{background:#273657;border:1px solid #3c4f78;border-radius:10px;padding:11px;font-weight:800;min-height:19px}
            QPushButton:hover{background:#394b78;border:1px solid #a78bfa}
            QPushButton#primary{background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #7c3aed,stop:1 #db2777);color:white;border:0}
            QPushButton#primary:hover{background:#9333ea}
            QPushButton#cyan{background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #0891b2,stop:1 #2563eb);color:white;border:0}
            QTabWidget::pane{border:1px solid #35466c;border-radius:12px;background:#111a30;top:-1px}
            QTabBar::tab{background:#202d4b;color:#cbd5e1;padding:10px 11px;margin:3px;border:1px solid #35466c;border-radius:9px;font-weight:800}
            QTabBar::tab:hover{background:#37466b;color:white}
            QTabBar::tab:selected{background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #7c3aed,stop:1 #db2777);color:white;border:0}
            QLabel#result{background:#0a1428;border:1px solid #2dd4bf;border-radius:11px;padding:14px;color:#99f6e4;font-size:15px;font-weight:800}
            QLabel#hint{color:#a5b4fc;background:#101a31;border-radius:7px;padding:5px}
            QLabel#footer{color:#a5b4fc;font-size:11px;padding:5px}
        )");
        connect(expression,&QLineEdit::returnPressed,this,[=]{lastAnswer=evaluate(expression->text());display->setText(lastAnswer);});
    }

private:
    QLineEdit *expression{};
    QLabel *display{};
    QTabWidget *tools{};
    QString lastAnswer="0";

    QWidget *toolPage() { auto *w=new QWidget;auto *l=new QVBoxLayout(w);l->setContentsMargins(13,14,13,13);l->setSpacing(10);return w; }
    QLabel *outLabel(QString s="Result will appear here"){auto *x=new QLabel(s);x->setObjectName("result");x->setWordWrap(true);return x;}
    QLineEdit *line(QString p,QString v={}){auto *e=new QLineEdit(v);e->setPlaceholderText(p);return e;}
    QPushButton *button(QString s){auto *b=new QPushButton(s);b->setObjectName("primary");return b;}

    class Parser {
    public:
        QString s,err;int p=0;
        Parser(QString x):s(x){s.remove(' ');}
        bool eat(QChar c){if(p<s.size()&&s[p]==c){++p;return true;}return false;}
        double expr(){double x=term();while(true){if(eat('+'))x+=term();else if(eat('-'))x-=term();else break;}return x;}
        double term(){double x=power();while(true){if(eat('*'))x*=power();else if(eat('/')){double y=power();if(y==0){err="Division by zero";return 0;}x/=y;}else break;}return x;}
        double power(){double x=unary();if(eat('^'))x=std::pow(x,power());return x;}
        double unary(){if(eat('+'))return unary();if(eat('-'))return -unary();return atom();}
        double atom(){
            if(eat('(')){double x=expr();if(!eat(')'))err="Missing )";return x;}
            if(p<s.size()&&(s[p].isDigit()||s[p]=='.')){int st=p;while(p<s.size()&&(s[p].isDigit()||s[p]=='.'||s[p]=='e'||s[p]=='E'||((s[p]=='+'||s[p]=='-')&&p>st&&(s[p-1]=='e'||s[p-1]=='E'))))++p;bool ok;double x=s.mid(st,p-st).toDouble(&ok);if(!ok)err="Bad number";return x;}
            int st=p;while(p<s.size()&&s[p].isLetter())++p;QString n=s.mid(st,p-st).toLower();
            if(n=="pi")return M_PI;if(n=="e")return M_E;
            if(n.isEmpty()){err="Unexpected character";return 0;}
            if(!eat('(')){err="Expected ( after "+n;return 0;}double v=expr();if(!eat(')'))err="Missing )";
            if(n=="sqrt")return v<0?NAN:std::sqrt(v);
            if(n=="sin")return std::sin(v*M_PI/180);if(n=="cos")return std::cos(v*M_PI/180);if(n=="tan")return std::tan(v*M_PI/180);
            if(n=="log")return v<=0?NAN:std::log10(v);if(n=="ln")return v<=0?NAN:std::log(v);
            err="Unknown function "+n;return 0;
        }
    };
    QString evaluate(QString s){Parser p(s);double v=p.expr();if(!p.err.isEmpty())return "Error: "+p.err;if(p.p<p.s.size())return "Error near "+p.s.mid(p.p);return fmt(v);}

    QWidget *infoTool(){
        auto*w=toolPage();auto*l=qobject_cast<QVBoxLayout*>(w->layout());
        l->addWidget(new QLabel("Convert information quantities across decimal and binary units."));
        auto*amount=new QDoubleSpinBox;amount->setRange(0,1e15);amount->setDecimals(6);amount->setValue(1024);
        auto*from=new QComboBox;auto*to=new QComboBox;
        QStringList units={"bit","byte","KB","MB","GB","TB","KiB","MiB","GiB"};
        from->addItems(units);to->addItems(units);from->setCurrentText("byte");to->setCurrentText("KiB");
        auto*form=new QFormLayout;form->addRow("Amount:",amount);form->addRow("From:",from);form->addRow("To:",to);l->addLayout(form);
        auto*out=outLabel();l->addWidget(buttonWithConnect("Convert information",[=]{double f[]={.125,1,1e3,1e6,1e9,1e12,1024,1048576,1073741824.0};out->setText(fmt(amount->value()*f[from->currentIndex()]/f[to->currentIndex()])+" "+to->currentText());}));l->addWidget(out);l->addStretch();return w;
    }
    QPushButton *buttonWithConnect(QString s,std::function<void()> fn){auto*b=button(s);connect(b,&QPushButton::clicked,this,fn);return b;}

    QWidget *entropyTool(){
        auto*w=toolPage();auto*l=qobject_cast<QVBoxLayout*>(w->layout());
        auto *title=new QLabel("INFORMATION CONTENT  |  BITS · NATS · DECITS");
        title->setObjectName("section"); l->addWidget(title);
        auto *desc=new QLabel("Enter one or more event probabilities, separated by commas or new lines. Each probability gets its own information value in bits, nats and decits. For a complete probability distribution, the values should sum to 1.");
        desc->setWordWrap(true);desc->setObjectName("hint");l->addWidget(desc);
        auto *probabilities = new QPlainTextEdit;
        probabilities->setPlaceholderText("Example:\n0.5\n0.25\n0.125\n0.125");
        probabilities->setPlainText("0.5\n0.25\n0.125\n0.125");
        probabilities->setMinimumHeight(105);l->addWidget(new QLabel("Event probabilities:"));l->addWidget(probabilities);
        auto *out=outLabel("Each event's information will appear here.");
        l->addWidget(buttonWithConnect("Calculate information for all events",[=]{
            QString raw=probabilities->toPlainText(); raw.replace(',', ' ');
            const QStringList parts=raw.split(QRegularExpression("\\s+"),Qt::SkipEmptyParts);
            if(parts.isEmpty()){out->setText("Enter at least one probability greater than 0 and at most 1.");return;}
            QString result="EVENT INFORMATION\n"; double sum=0; int index=0;
            for(const QString &part:parts){
                bool ok=false; double p=part.toDouble(&ok);
                if(!ok||p<=0||p>1){out->setText("Invalid probability: "+part+"\nEach probability must be greater than 0 and at most 1.");return;}
                ++index;sum+=p;
                result += "\nEvent "+QString::number(index)+"  |  p = "+fmt(p)
                    +"\n  Bits: "+fmt(-std::log2(p))+" bits\n  Nats: "+fmt(-std::log(p))
                    +" nats\n  Decits: "+fmt(-std::log10(p))+" decits\n";
            }
            result += "\nSum of probabilities = "+fmt(sum);
            if(std::abs(sum-1.0)<1e-8) result += "\nValid complete distribution (sum = 1).";
            else if(sum<1.0) result += "\nProbabilities sum to less than 1; this may be an incomplete distribution.";
            else result += "\nWarning: probabilities sum to more than 1, so they do not form a valid mutually exclusive distribution.";
            out->setText(result);
        }));
        l->addWidget(out);
        l->addWidget(new QLabel("Per event: bits = −log₂(p), nats = −ln(p), decits = −log₁₀(p). This calculates event information, not Shannon entropy."));
        l->addStretch();return w;
    }
    QWidget *shannonEntropyTool(){
        auto*w=toolPage();auto*l=qobject_cast<QVBoxLayout*>(w->layout());
        auto *title=new QLabel("SHANNON ENTROPY  |  DISTRIBUTION UNCERTAINTY");
        title->setObjectName("section");l->addWidget(title);
        auto *desc=new QLabel("Enter all event probabilities for a distribution. Shannon entropy is the probability-weighted average information: H = −Σ pᵢ logᵦ(pᵢ). Probabilities must be between 0 and 1 and sum to 1.");
        desc->setWordWrap(true);desc->setObjectName("hint");l->addWidget(desc);
        auto *probabilities=new QPlainTextEdit;
        probabilities->setPlaceholderText("Example:\n0.5\n0.25\n0.125\n0.125");
        probabilities->setPlainText("0.5\n0.25\n0.125\n0.125");
        probabilities->setMinimumHeight(105);l->addWidget(new QLabel("Event probabilities (comma or new-line separated):"));l->addWidget(probabilities);
        auto *out=outLabel("Shannon entropy results will appear here.");
        l->addWidget(buttonWithConnect("Calculate Shannon entropy",[=]{
            QString raw=probabilities->toPlainText();raw.replace(',', ' ');
            const QStringList parts=raw.split(QRegularExpression("\\s+"),Qt::SkipEmptyParts);
            if(parts.isEmpty()){out->setText("Enter at least two probabilities that sum to 1.");return;}
            double sum=0, hBits=0, hNats=0, hDecits=0;
            for(const QString &part:parts){bool ok=false;double p=part.toDouble(&ok);
                if(!ok||p<0||p>1){out->setText("Invalid probability: "+part+"\nEach probability must be between 0 and 1.");return;}
                sum+=p;if(p>0){hBits-=p*std::log2(p);hNats-=p*std::log(p);hDecits-=p*std::log10(p);}
            }
            if(std::abs(sum-1.0)>1e-8){out->setText("Probabilities must sum to 1.\nCurrent sum = "+fmt(sum));return;}
            out->setText("Shannon entropy H = −Σ pᵢ logᵦ(pᵢ)\n\nBits (base 2): "+fmt(hBits)+" bits\nNats (base e): "+fmt(hNats)+" nats\nDecits (base 10): "+fmt(hDecits)+" decits\n\nProbability sum = "+fmt(sum));
        }));
        l->addWidget(out);l->addWidget(new QLabel("Unlike per-event information, entropy averages information across the full probability distribution."));l->addStretch();return w;
    }
    QWidget *numberTool(){
        auto*w=toolPage();auto*l=qobject_cast<QVBoxLayout*>(w->layout());
        auto*input=line("Enter integer","255");input->setText("255");auto*from=new QComboBox;auto*to=new QComboBox;
        QStringList bases={"Binary (2)","Octal (8)","Decimal (10)","Hexadecimal (16)"};from->addItems(bases);to->addItems(bases);from->setCurrentIndex(2);
        auto*f=new QFormLayout;f->addRow("Number:",input);f->addRow("Input base:",from);f->addRow("Output base:",to);l->addLayout(f);auto*out=outLabel();
        l->addWidget(buttonWithConnect("Convert number",[=]{int bs[]={2,8,10,16};bool ok;qlonglong n=input->text().trimmed().toLongLong(&ok,bs[from->currentIndex()]);if(!ok)out->setText("Invalid integer for selected base.");else out->setText("Converted = "+QString::number(n,bs[to->currentIndex()]).toUpper()+"\nDecimal = "+QString::number(n));}));l->addWidget(out);l->addStretch();return w;
    }
    QWidget *efficiencyTool(){
        auto*w=toolPage();auto*l=qobject_cast<QVBoxLayout*>(w->layout());auto*useful=new QDoubleSpinBox;auto*input=new QDoubleSpinBox;
        useful->setRange(0,1e15);useful->setValue(80);input->setRange(0,1e15);input->setValue(100);
        auto*f=new QFormLayout;f->addRow("Useful output:",useful);f->addRow("Total input:",input);l->addLayout(f);auto*out=outLabel();
        l->addWidget(buttonWithConnect("Calculate efficiency",[=]{if(input->value()<=0)out->setText("Input must be greater than zero.");else{double v=100*useful->value()/input->value();out->setText("Efficiency = "+fmt(v)+"%"+(v>100?" — check values":""));}}));l->addWidget(out);
        l->addWidget(new QLabel("Efficiency = (useful output ÷ total input) × 100%."));l->addStretch();return w;
    }
    QWidget *formulaTool(){
        auto*w=toolPage();auto*l=qobject_cast<QVBoxLayout*>(w->layout());auto*type=new QComboBox;
        type->addItems({"Rectangle area + perimeter","Circle area + circumference","Triangle area","Simple interest","Distance = speed × time","BMI (kg, metres)","Pythagorean theorem"});l->addWidget(type);
        auto*a=new QDoubleSpinBox;auto*b=new QDoubleSpinBox;auto*c=new QDoubleSpinBox;for(auto*x:{a,b,c}){x->setRange(-1e9,1e9);x->setDecimals(5);}
        auto*f=new QFormLayout;f->addRow("Value A:",a);f->addRow("Value B:",b);f->addRow("Value C:",c);l->addLayout(f);auto*out=outLabel();
        l->addWidget(buttonWithConnect("Calculate formula",[=]{double x=a->value(),y=b->value(),z=c->value();QString s;switch(type->currentIndex()){
            case 0:s="Area = "+fmt(x*y)+"\nPerimeter = "+fmt(2*(x+y));break;
            case 1:s="Area = "+fmt(M_PI*x*x)+"\nCircumference = "+fmt(2*M_PI*x);break;
            case 2:s="Triangle area = "+fmt(x*y/2);break;
            case 3:s="Interest = "+fmt(x*y*z/100)+"\nTotal = "+fmt(x+x*y*z/100);break;
            case 4:s="Distance = "+fmt(x*y);break;
            case 5:s=y<=0?"Height must be greater than zero.":"BMI = "+fmt(x/(y*y));break;
            case 6:s="Hypotenuse = "+fmt(std::sqrt(x*x+y*y));break;
        }out->setText(s);}));l->addWidget(out);l->addWidget(new QLabel("A/B/C meanings depend on the selected formula."));l->addStretch();return w;
    }
    QWidget *currencyTool(){
        auto*w=toolPage();auto*l=qobject_cast<QVBoxLayout*>(w->layout());l->addWidget(new QLabel("Offline estimate with editable example rates. Rates are value of 1 unit in INR; not live quotes."));
        auto*amount=new QDoubleSpinBox;amount->setRange(0,1e12);amount->setDecimals(2);amount->setValue(100);
        auto*from=new QComboBox;auto*to=new QComboBox;QStringList codes={"INR","USD","EUR","GBP","JPY","CAD","AUD"};from->addItems(codes);to->addItems(codes);from->setCurrentText("USD");to->setCurrentText("INR");
        auto*f=new QFormLayout;f->addRow("Amount:",amount);f->addRow("From:",from);f->addRow("To:",to);l->addLayout(f);
        auto*rates=new QPlainTextEdit("INR=1\nUSD=83\nEUR=90\nGBP=105\nJPY=0.56\nCAD=61\nAUD=55");rates->setMaximumHeight(145);l->addWidget(new QLabel("Edit sample rates if needed:"));l->addWidget(rates);auto*out=outLabel();
        l->addWidget(buttonWithConnect("Convert currency",[=]{QMap<QString,double>r;for(QString line:rates->toPlainText().split('\n',Qt::SkipEmptyParts)){auto p=line.split('=');if(p.size()==2){bool ok;double v=p[1].trimmed().toDouble(&ok);if(ok&&v>0)r[p[0].trimmed().toUpper()]=v;}}QString f=from->currentText(),t=to->currentText();if(!r.contains(f)||!r.contains(t))out->setText("Add valid positive rates for both currencies.");else out->setText(fmt(amount->value())+" "+f+" ≈ "+fmt(amount->value()*r[f]/r[t])+" "+t+"\nExample rates only — not a live market quote.");}));l->addWidget(out);l->addStretch();return w;
    }
};
int main(int argc,char*argv[]){QApplication app(argc,argv);QApplication::setStyle("Fusion");SmartCalculator w;w.show();return app.exec();}
#include "main.moc"
