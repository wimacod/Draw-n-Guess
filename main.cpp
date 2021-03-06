#include "Header.h"
using namespace std;

int main()
{
    Draw_window *w = new Draw_window();
    FFN *DIGITnetwork = new FFN();
    DIGITnetwork->initFFN(43, 20, 10);

    vector<vector<float>> Xapp = readMatFromFile("data_set/new/Xapp.txt");
    vector<vector<float>> Ta = readMatFromFile("data_set/new/TA.txt");
    vector<vector<float>> Xtest = readMatFromFile("data_set/new/Xtest.txt");
    vector<vector<float>> Tt = readMatFromFile("data_set/new/TT.txt");
    
    cout << "Training Neural Network... Please Wait..." << endl;
    DIGITnetwork->train_by_iteration(Xapp,Ta,1000);
    DIGITnetwork->test(Xtest,Tt);
    

    while(1){
        w->set_active(true);
        w->run();

        deque<deque<int>> data32 = *(w->get_draw_mat());
        deque<deque<int>> data32_centered = center_mat(data32);
        affiche_mat(data32_centered, 32, 32);
        deque<deque<int>> data8 = compress_mat(data32_centered);
        vector<float> draw_variables = pca(normalize(extract_variables(data8)));
        
        DIGITnetwork->sim(draw_variables);
        vector<float> current_output = DIGITnetwork->get_ffn_outputs();
        int guess = distance(current_output.begin(),
                              max_element(current_output.begin(),
                                          current_output.end()));
        cout << "Best Guess : " << guess << endl;
        w->set_guess_text(to_string(guess));
    }
    return 0;
}
