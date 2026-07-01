#include "antrean_wahana.h"

void CreateAntrean(AntreanWahana *aw, int startTime) {
    CreateQueue(&aw->prioritas);
    CreateQueue(&aw->regular);
    aw->currentTime         = startTime;
    aw->priorityServedCount = 0;
}

boolean isAllEmpty(AntreanWahana aw) {
    return (isEmpty(aw.prioritas) && isEmpty(aw.regular));
}

boolean isPrioritasEmpty(AntreanWahana aw) {
    return isEmpty(aw.prioritas);
}

boolean isRegularEmpty(AntreanWahana aw) {
    return isEmpty(aw.regular);
}

int totalLength(AntreanWahana aw) {
    return length(aw.prioritas) + length(aw.regular);
}

int lengthPrioritas(AntreanWahana aw) {
    return length(aw.prioritas);
}

int lengthRegular(AntreanWahana aw) {
    return length(aw.regular);
}

void AddPengunjung(AntreanWahana *aw, Pengunjung p, boolean isPriority) {
    if (isPriority) {
        enqueue(&aw->prioritas, p);
    } else {
        enqueue(&aw->regular, p);
    }
}

boolean ServeNext(AntreanWahana *aw, Pengunjung *served) {
    if (isAllEmpty(*aw)) {
        return false;
    }

    if (aw->priorityServedCount >= STARVATION_THRESHOLD && !isRegularEmpty(*aw)) {
        dequeue(&aw->regular, served);
        aw->priorityServedCount = 0;
        return true;
    }

    if (!isPrioritasEmpty(*aw)) {
        dequeue(&aw->prioritas, served);
        aw->priorityServedCount++;
        return true;
    }

    dequeue(&aw->regular, served);
    aw->priorityServedCount = 0;
    return true;
}

void RemoveTimedOut(AntreanWahana *aw) {
    Pengunjung p;

    int lenP = lengthPrioritas(*aw);
    for (int i = 0; i < lenP; i++) {
        dequeue(&aw->prioritas, &p);
        if ((aw->currentTime - p.arrivalTime) <= p.patience) {
            enqueue(&aw->prioritas, p);
        }
    }

    int lenR = lengthRegular(*aw);
    for (int i = 0; i < lenR; i++) {
        dequeue(&aw->regular, &p);
        if ((aw->currentTime - p.arrivalTime) <= p.patience) {
            enqueue(&aw->regular, p);
        }
    }
}

void UpdateTime(AntreanWahana *aw, int newTime) {
    if (newTime >= aw->currentTime) {
        aw->currentTime = newTime;
    }
}

Pengunjung PeekNextPrioritas(AntreanWahana aw) {
    return front(aw.prioritas);
}

Pengunjung PeekNextRegular(AntreanWahana aw) {
    return front(aw.regular);
}