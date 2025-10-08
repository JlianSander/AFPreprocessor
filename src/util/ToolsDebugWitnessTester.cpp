#include "../../include/util/ToolsDebugWitnessTester.h"

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/


bool tools::WitnessTester::test(uint32_t query_argument, AF &framework, const std::string& file_path)
{
	// initialize variables
    ArrayBitSet actv_args = framework.create_active_arguments();
    std::list<uint32_t> witness_all = tools::Tools_Debug::read_witness(file_path);
	ArrayBitSet active_args_in_coi = ArrayBitSet();
	
	ConeOfInfluence coi(framework);
	list<uint32_t> grounded_extension;
    std::list<uint32_t> not_found;
	std::list<uint32_t> remaining;

	// // ------------------------ DEBUG ----------------------------------------------------------------------
	// 	std::cout << "============  Before starting Preprocessing  ============" << std::endl;
	// 	ArrayBitSet actv_args = framework.create_active_arguments();
	// 	std::list<uint32_t> args; // list of arguments that are of relevance
	// 	tools::Tools_List::copy_in_list(args, actv_args._array);
	// 	std::string filePath = "/home/jsander/reducto/debug/witness.txt";   // Path to the file

	// 	tools::Tools_Debug::print_Msg_ContainsNumbersOfWitness(framework, filePath, args);
	// // ------------------------ DEBUG ----------------------------------------------------------------------

	// preprocess the framework
	PreProc_GR::process(framework, query_argument, true, true, active_args_in_coi, grounded_extension, coi);

	std::cout << "============  After Preprocessing  ============" << std::endl;
	std::list<uint32_t> args_coi; // list of arguments that are of relevance
	tools::Tools_List::copy_in_list(args_coi, active_args_in_coi._array);
	std::list<uint32_t> args_2 = tools::Tools_List::extend_list(args_coi, grounded_extension);
	tools::Tools_Debug::compare_witness_to_list(file_path, args_2, false, true, not_found, remaining);

	std::cout << "============  Without Grounded Extension  ============" << std::endl;
	tools::Tools_Debug::compare_witness_to_list(file_path, args_coi, false, true, not_found, remaining);

	cout << "The following arguments attack the query argument: " << endl;
	std::list<uint32_t> attackers = tools::Tools_Debug::get_active_attackers(framework, active_args_in_coi, query_argument);
	Printer::print_list(attackers);
	cout << endl;

	cout << "The following arguments of the witness attack the query argument: " << endl;
	std::list<uint32_t> attackers_in_witness = tools::Tools_List::create_intersection(attackers, remaining);
	Printer::print_list(attackers_in_witness);
	cout << endl;

	cout << "The COI reduced by the remaining witness arguments contains the following arguments: " << endl;
	ArrayBitSet reduct =  Reduct::get_reduct_set(active_args_in_coi, framework, remaining);
	Printer::print_vector(reduct._array);
	cout << endl;

	// cout << "Complete Witness: " << endl;
	// Printer::print_list(witness_all);
	// cout << endl;

	ArrayBitSet reduct_all =  Reduct::get_reduct_set(actv_args, framework, witness_all);
	cout << "The original AF reduced by the witness contains " << reduct_all._array.size() << " arguments: " << endl;
	//Printer::print_vector(reduct_all._array);
	cout << endl;

    list<uint32_t> extension_in_reduct;
    bool has_complete_extension_in_reduct = Solver_DC_CO::solve_reduct(query_argument, framework, reduct_all, extension_in_reduct);

    if(has_complete_extension_in_reduct){
        cout << "Found the following CO extension in the reduct:" << endl;
        Printer::print_list(extension_in_reduct);
        cout << endl;

        std::list<uint32_t> witness_superset = tools::Tools_List::extend_list(witness_all, extension_in_reduct);
        cout << "Found the following superset of the witness containing the query argument:" << endl;
        Printer::print_list(witness_superset);
        cout << endl;
    }

    return !has_complete_extension_in_reduct;
	}