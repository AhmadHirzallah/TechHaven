```mermaid
sequenceDiagram
    title Comprehensive Forking & Waiting Explanation (Page 1: id1/id2 FORKING)

    participant MAIN as Original Main

    MAIN->>MAIN: id1 = fork()
    Note right of MAIN
        Splits into:
        • Parent (id1 != 0)
        • Child  (id1 == 0)
    end note

    MAIN->>MAIN: id2 = fork()
    Note right of MAIN
        Each of the 2 processes calls fork() again → total 4 processes:
        1) Parent:  (id1 != 0, id2 != 0)
        2) x:       (id1 == 0, id2 != 0)
        3) z:       (id1 != 0, id2 == 0)
        4) y:       (id1 == 0, id2 == 0)
    end note

    alt (id1 == 0 and id2 == 0)
        Note right of MAIN: We are process (y)
    else (id1 == 0 and id2 != 0)
        Note right of MAIN: We are process (x)
    else (id1 != 0 and id2 == 0)
        Note right of MAIN: We are process (z)
    else (id1 != 0 and id2 != 0)
        Note right of MAIN: We are the (Parent) process
    end

    Note over MAIN
        After these forks, each process runs:

        while (wait(NULL) != -1 || errno != ECHILD)
            printf("Waited for a child to finish !!!\n");

        Explanation:
        • wait(NULL) reaps one child if available; returns its PID or -1 on error.
        • If it returns -1 and errno == ECHILD, there are NO more children to reap.
        • If errno != ECHILD, the error might be something else, so we keep trying.
        • This loop ensures that each process that DOES have children won't stop
          waiting after reaping just one child, preventing zombie processes.
    end note
