#include "epframebuffer.h"
#include <QImage>
#include <QPainter>
#include <QRect>
#include <QTimer>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <QCoreApplication>

#define MS(x) std::chrono::duration_cast<std::chrono::milliseconds>(x).count()
void testDraw(const QImage &scaledArtwork, DEFAULT_EPFR_CLASS *framebuffer, int offsetX, int offsetY, EPContentType epct, EPScreenMode type, int flags) {
    std::cout << "Drawing image on offset position " << offsetX << " " << offsetY << "...\n"
        << "EPContentType: " << epct << ", EPScreenMode: " << type << ", flags: " << flags << std::endl;
    QPainter dest(&framebuffer->auxBuffer);
    dest.drawImage(scaledArtwork.width() * offsetX, scaledArtwork.height() * offsetY, scaledArtwork);
    auto start = std::chrono::high_resolution_clock::now();
    auto startAll = start;
    framebuffer->swapBuffers(QRect(scaledArtwork.width() * offsetX, scaledArtwork.height() * offsetY, scaledArtwork.width(), scaledArtwork.height()), epct, type, flags ? EPFramebuffer::UpdateFlag::CompleteRefresh : EPFramebuffer::UpdateFlag::NoRefresh);
    std::cout << "Buffers swapped" << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto diffA = end - start;
    start = std::chrono::high_resolution_clock::now();
    framebuffer->sync();
    std::cout << "Sync complate!" << std::endl;
    end = std::chrono::high_resolution_clock::now();
    auto diffB = end - start;
    auto diffAll = end - startAll;
    std::cout << "Drawing took " << MS(diffA) << "ms, syncing took " << MS(diffB) << "ms - total: " << MS(diffAll) << "ms." << std::endl << std::endl;
}

void run(){
    DEFAULT_EPFR_CLASS *framebuffer = EPFramebuffer::instance();
    QImage artwork("/tmp/art.png");
    QImage scaledArtwork = artwork.scaled(QSize(270, 10), Qt::KeepAspectRatioByExpanding);

    int oY = 0;
    for(int contentType = 0; contentType <= 1; contentType++){
        for(int epsm = 0; epsm <= 5; epsm++) {
            testDraw(scaledArtwork, framebuffer, epsm, oY, (EPContentType) contentType, (EPScreenMode) epsm, 0);
            sleep(1);
        }
        oY++;
    }

}

int main(int argc, char **argv){
    QCoreApplication app(argc, argv);

    // Schedule runTest to execute after event loop starts
    QTimer::singleShot(0, &run);

    return app.exec();
}
