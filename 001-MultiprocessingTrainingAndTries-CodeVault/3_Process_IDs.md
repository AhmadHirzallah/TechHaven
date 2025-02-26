```mermaid
sequenceDiagram
    title Process Fork, Wait, and Zombie Prevention Visualization

    participant MP as Main Process

    MP->>MP: int id = fork()
    Note right of MP: fork() creates two execution flows:<br/> - Child Process (id == 0)<br/> - Parent Process (id != 0)

    alt Child Process (id == 0)
        participant CP as Child Process
        Note right of CP: In Child Process:<br/> - Executes sleep(1) to simulate delay<br/> - Delay may allow parent to finish first, risking zombie creation<br/> - Memory isn’t freed if the child remains active!
        MP->>CP: sleep(1)
        CP->>CP: printf("Current ID: (%d)\nParent ID: (%d)")
        Note right of CP: After printing, the child terminates.<br/> If not reaped properly, it becomes a zombie.
    else Parent Process (id != 0)
        participant PP as Parent Process
        Note right of PP: In Parent Process:<br/> - Prints its own IDs immediately<br/> - Must wait for child termination to avoid zombies<br/> - Rule: Always wait for child before terminating.
        MP->>PP: printf("Current ID: (%d)\nParent ID: (%d)")
        PP->>PP: wait(NULL)
        Note right of PP: wait(NULL) blocks the parent until the child finishes,<br/> preventing zombie processes and ensuring memory cleanup.
    end

    %% Alternative Approach: Checking wait() Result
    Note over MP: Optionally, store the wait() result to check which child terminated.
    MP->>MP: int wait_res = wait(NULL)
    
    alt Successful wait
        Note right of MP: wait() returns the child’s PID,<br/> indicating the child finished execution.
        MP->>MP: printf("(%d) process finished execution!", wait_res)
    else No Child
        Note right of MP: wait() returns -1 when there are no child processes.
        MP->>MP: printf("No Children to wait for")
    end

    Note over MP: **Key Points:**<br/> - Every child must have a parent.<br/> - If a parent terminates before its child, the child is reparented (often to init) and may become a zombie.<br/> - Not freeing a non-terminated child’s memory can lead to leaks.<br/> - Using wait(NULL) ensures orderly termination and resource cleanup.
