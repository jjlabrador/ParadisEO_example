// moeo general include
#include <moeo>
#include <es/eoRealInitBounded.h>
// how to initialize the population
#include <do/make_pop.h>
// the stopping criterion
#include <do/make_continue_moeo.h>
// outputs (stats, population dumps, ...)
#include <do/make_checkpoint_moeo.h>
// evolution engine (selection and replacement)
#include <do/make_ea_moeo.h>
// simple call to the algo
#include <do/make_run.h>

// checks for help demand, and writes the status file and make_help; in libutils
void make_help(eoParser & _parser);
// definition of the representation
#include <ZDT.h>
#include <ZDT1Eval.h>
#include <ZDT2Eval.h>
#include <SBXCrossover.h>
#include <PolynomialMutation.h>

using namespace std;

int main(int argc, char* argv[])
{
    try
    {

        eoParser parser(argc, argv);  // for user-parameter reading
        eoState state;                // to keep all things allocated

        unsigned int MAX_GEN = parser.createParam((unsigned int)(10000), "maxGen", "Maximum number of generations",'G',"Param").value();
        double P_CROSS = parser.createParam(1.0, "pCross", "Crossover probability",'C',"Param").value();
        double EXT_P_MUT = parser.createParam(1.0, "extPMut", "External Mutation probability",'E',"Param").value();
        double INT_P_MUT = parser.createParam(0.083, "intPMut", "Internal Mutation probability",'I',"Param").value();
        unsigned int VEC_SIZE = parser.createParam((unsigned int)(30), "vecSize", "Genotype Size",'V',"Param").value();
        unsigned int NB_OBJ= parser.createParam((unsigned int)(2), "nbObj", "Number of Objective",'N',"Param").value();
        std::string OUTPUT_FILE = parser.createParam(std::string("zdt_nsgaII"), "outputFile", "Path of the output file",'o',"Output").value();
        unsigned int EVAL = parser.createParam((unsigned int)(1), "eval", "Number of the ZDT evaluation fonction",'F',"Param").value();
        unsigned int NB_EVAL = parser.createParam((unsigned int)(0), "nbEval", "Number of evaluation before Stop",'P',"Param").value();
        unsigned int TIME = parser.createParam((unsigned int)(0), "time", "Time(seconds) before Stop",'T',"Param").value();


        /*** the representation-dependent things ***/
        std::vector <bool> bObjectives(2);
        for (unsigned int i=0; i<2 ; i++)
            bObjectives[i]=true;
        moeoObjectiveVectorTraits::setup(2,bObjectives);

        // The fitness evaluation
        eoEvalFunc <ZDT> * eval;

        if (EVAL == 1)
            eval= new ZDT1Eval;
        else if (EVAL == 2)
            eval= new ZDT2Eval;

        eoEvalFuncCounter<ZDT> evalFunc(*eval);

        // the genotype (through a genotype initializer)
        eoRealVectorBounds bounds(VEC_SIZE, 0.0, 1.0);

        eoRealInitBounded <ZDT> init (bounds);

        // the variation operators
        SBXCrossover < ZDT > xover(bounds, 15);

        PolynomialMutation < ZDT > mutation (bounds, INT_P_MUT, 20);

        eoSGAGenOp < ZDT > op(xover, P_CROSS, mutation, EXT_P_MUT);

	//continuators

        eoGenContinue<ZDT> term(MAX_GEN);

        eoCheckPoint<ZDT>* checkpoint;

        if (TIME > 0)
            checkpoint = new eoCheckPoint<ZDT>(*(new eoTimeContinue<ZDT>(TIME)));
        else if (NB_EVAL > 0)
            checkpoint = new eoCheckPoint<ZDT>(*(new eoEvalContinue<ZDT>(evalFunc, NB_EVAL)));
        else {
            cout << "ERROR!!! : TIME or NB_EVAL must be > 0 : used option --time or --nbEval\n";
            return EXIT_FAILURE;
        }

        checkpoint->add(term);

	//algorithm

        moeoNSGAII<ZDT> algo(*checkpoint, evalFunc ,op);

	//Initialization of population	

        eoPop<ZDT>& pop = do_make_pop(parser, state, init);

        /*** Go ! ***/
	
        do_run(algo, pop);

        // help ?
        make_help(parser);

	//Print the Pareto Front
        moeoUnboundedArchive<ZDT> finalArchive;
        finalArchive(pop);

        ofstream outfile(OUTPUT_FILE.c_str(), ios::app);
        if ((unsigned int)outfile.tellp() != 0)
            outfile << endl;

        for (unsigned int i=0 ; i < finalArchive.size(); i++) {
            for (unsigned int j=0 ; j<NB_OBJ; j++) {
                outfile << finalArchive[i].objectiveVector()[j];
                if (j != NB_OBJ -1)
                    outfile << " ";
            }
            outfile << endl;
        }

        outfile.close();

    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
    return EXIT_SUCCESS;
}
