
static const float kThreshold = 0.00001f; 

export void sqrt_ispc(uniform int N,
                      uniform float initialGuess,
                      uniform float values[],
                      uniform float output[])
{
    foreach (i = 0 ... N) {

        float x = values[i];
        float guess = initialGuess;

        float pred = abs(guess * guess * x - 1.f);

        while (pred > kThreshold) {
            guess = (3.f * guess - x * guess * guess * guess) * 0.5f;
            pred = abs(guess * guess * x - 1.f);
        }

        output[i] = x * guess;
        
    }
}

task void sqrt_ispc_task(uniform int N,
                         uniform int span,
                         uniform float initialGuess,
                         uniform float values[],
                         uniform float output[])
{
    //uniform代表实例内一致性与任务间隔离性
    //所以每个任务的indexStart/End是不一样的
    //但是每个任务的实例间的indexStart/End是一样的
    //比如向量宽度为8，则这8个实例共享indexStart/End
    //任务代表的是用了多少个向量寄存器。
    //实例代表向量寄存器的宽度，也就是一次处理几个数据（不够准确，但大致是这么个意思，严格意义是逻辑上的并行执行单位，和向量宽度相关但不等同）。
    uniform int indexStart = taskIndex * span;
    uniform int indexEnd = min(N, indexStart + span);
    
    foreach (i = indexStart ... indexEnd) {

        float x = values[i];
        float guess = initialGuess;

        float pred = abs(guess * guess * x - 1.f);

        while (pred > kThreshold) {
            guess = (3.f * guess - x * guess * guess * guess) * 0.5f;
            pred = abs(guess * guess * x - 1.f);
        }

        output[i] = x * guess;
    
    }
}

export void sqrt_ispc_withtasks(uniform int N,
                                uniform float initialGuess,
                                uniform float values[],
                                uniform float output[])
{

    uniform int span = N / 64;  // 64 tasks

    launch[N/span] sqrt_ispc_task(N, span, initialGuess, values, output);
}
