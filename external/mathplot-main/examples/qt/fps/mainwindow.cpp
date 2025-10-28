#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <sm/vec>
#include <sm/vvec>
#include <sm/hexgrid>

#include <mplot/qt/viswidget.h>
#include <mplot/GraphVisual.h>
#include <mplot/TriangleVisual.h>
#include <mplot/HexGridVisual.h>
#include <mplot/ScatterVisual.h>

#include <QVBoxLayout>
#include <QFrame>
#include <QGridLayout>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->viswidget_init();

    // Call a function to set up a first VisualModel in the viswidget
    this->setupHexGridVisual();

    // Example timer to carry out computations. Here, a lambda function modifies the data that's visualised on the HexGrid
    auto timer = new QTimer(parent);
    connect(timer, &QTimer::timeout, [this]{
                                         for (unsigned int hi=0; hi<this->hg->num(); ++hi) {
                                             this->r[hi] = std::sqrt (hg->d_x[hi]*hg->d_x[hi] + hg->d_y[hi]*hg->d_y[hi]);
                                             this->data[hi] = std::sin(k*r[hi])/k*r[hi];
                                         }
                                         this->k += 0.02f;
                                         if (this->k > 8.0f) { this->k = 1.0f; }
                                         // Access the pointer for the viswidget and set
                                         // needs_reinit to the index of the model that requires
                                         // reinitialization. When paintGL is called (and a GL
                                         // context is available) the mathplot OpenGL model will
                                         // be rebuilt.
                                         static_cast<mplot::qt::viswidget*>(this->p_vw)->set_model_needs_reinit (0);
                                         // Call the OpenGLWidget's update method. This will cause a
                                         // call to viswidget::paintGL()
                                         this->p_vw->update();
                                     });
    timer->start();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setupHexGridVisual()
{
    // First set up the hexgrid
    this->hg = std::make_unique<sm::hexgrid> (0.02f, 15.0f, 0.0f);
    this->hg->setCircularBoundary (4.0f);

    // Make some dummy data (a radially symmetric Bessel fn) to make an interesting surface
    this->data.resize (this->hg->num(), 0.0f);
    this->r.resize (this->hg->num(), 0.0f);
    this->k = 1.0f;
    for (unsigned int hi=0; hi<this->hg->num(); ++hi) {
        this->r[hi] = std::sqrt (hg->d_x[hi]*hg->d_x[hi] + hg->d_y[hi]*hg->d_y[hi]);
        this->data[hi] = std::sin(k*r[hi])/k*r[hi];
    }

    // Now create the HexGridVisual
    sm::vec<float, 3> offset = { 0.0f, -0.05f, 0.0f };
    auto hgv = std::make_unique<mplot::HexGridVisual<float, mplot::qt::gl_version>>(hg.get(), offset);

    // In general, you need to bindmodel before calling finalize() (esp. for
    // VisualModels that do text, like a GraphVisual). This gives the VisualModel access
    // to shader progs from the Visual environment, and allows the VisualModel to know
    // its parent Visual.
    static_cast<mplot::qt::viswidget*>(this->p_vw)->v.bindmodel (hgv);

    // Give the HexGridVisual access to the scalar data for the surface
    hgv->setScalarData (&this->data);

    // Now add the HexGridVisual model to newvisualmodels. It has to be cast to a plain mplot::VisualModel first:
    std::unique_ptr<mplot::VisualModel<mplot::qt::gl_version>> vmp = std::move (hgv);
    // The vector of VisualModels lives in viswidget, accessible via p_vw:
    static_cast<mplot::qt::viswidget*>(this->p_vw)->newvisualmodels.push_back (std::move(vmp));
}

void MainWindow::viswidget_init()
{
    // Create widget. Seems to open in its own window with a new context.
    mplot::qt::viswidget* vw = new mplot::qt::viswidget (this->parentWidget());
    // Choose lighting effects if you want
    vw->v.lightingEffects();
    // Add the OpenGL widget to the UI.
    this->ui->verticalLayout->addWidget (vw);
    // Keep a copy of vw
    this->p_vw = vw;
}

void MainWindow::on_actionQuit_triggered() { close(); }
