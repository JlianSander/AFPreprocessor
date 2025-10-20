#include "../include/Main.h"

using namespace std;

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

void static print_usage()
{
	cout << "Usage: " << PROGRAM_NAME << " -f <file> -fo <format> -a <query>\n\n";
	cout << "  <file_input>      input argumentation framework\n";
	cout << "  <format>          file format for input AF; for a list of available formats use option --formats\n";
	cout << "  <query>           query argument\n";
	cout << "  <file_output>     file to save simplified framework to\n";
	cout << "  <file_args>       file to save encoding of arguments to\n";
	cout << "Options:\n";
	cout << "  --help      Displays this help message.\n";
	cout << "  --version   Prints version and author information.\n";
	cout << "  --formats   Prints available file formats.\n";
	cout << "  --quiet     Surpresses printouts to console\n";
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

void static print_version()
{
	cout << PROGRAM_NAME << " (version "<< VERSIONNUMBER <<")\n"
		<< "Lars Bengel, University of Hagen <lars.bengel@fernuni-hagen.de>\n" 
		<< "Julian Sander, University of Hagen <julian.sander@fernuni-hagen.de>\n"
		<< "Matthias Thimm, University of Hagen <matthias.thimm@fernuni-hagen.de>\n";
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

void static print_formats()
{
	cout << "[i23,tgf]\n";
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

bool static check_query(uint32_t query, char **argv)
{
	if (query == 0) {
		cerr << argv[0] << ": Query argument must be specified via -a flag\n";
		return false;
	}
	return true;
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

int static execute(int argc, char **argv)
{
	// read command arguments
	if (argc == 1) {
		print_version();
		return 0;
	}

	int option_index = 0;
	int opt = 0;
	string file_input_af, file_output_af, file_output_args, fileformat, query;

	while ((opt = getopt_long_only(argc, argv, "", longopts, &option_index)) != -1) {
		switch (opt) {
		case 0:
			break;
		case 'f':
			file_input_af = optarg;
			break;
		case 'o':
			fileformat = optarg;
			break;
		case 'a':
			query = optarg;
			break;
		case 'r':
			file_output_af = optarg;
			break;
		case 'e':
			file_output_args = optarg;
			break;
		default:
			return 1;
		}
	}

	if (version_flag) {
		print_version();
		return 0;
	}

	if (usage_flag) {
		print_usage();
		return 0;
	}

	if (formats_flag) {
		print_formats();
		return 0;
	}

	if (file_input_af.empty()) {
		cerr << argv[0] << ": Input file must be specified via -f flag\n";
		return 1;
	}

	if (fileformat.empty()) {
		fileformat = file_input_af.substr(file_input_af.find_last_of(".") + 1, file_input_af.length() - file_input_af.find_last_of(".") - 1);
	}

	// parse the framework
	AF framework_input;
	uint32_t query_argument_input = 0;
	switch (Enums::string_to_format(fileformat)) {
		case I23:
			query_argument_input = ParserICCMA::parse_af_i23(framework_input, query, file_input_af);
			break;
		case TGF:
			query_argument_input = ParserICCMA::parse_af_tgf(framework_input, query, file_input_af);
			break;
		default:
			cerr << argv[0] << ": Unsupported file format\n";
			return 1;
	}
	// check if query argument is valid
	check_query(query_argument_input, argv);
	
	// maping the arguments of the simplified output framework to the arguments of the original input framework 
	std::map<uint32_t, uint32_t> args_output_to_input;
	AF framework_simplified_output = PreProcessor::calculate_cone_influence(framework_input, query_argument_input, args_output_to_input);

	if(!file_output_args.empty())
	{
		Writer::write_map_to_file(file_output_args, args_output_to_input, quiet_flag);
	}
	
	Writer::write_af_to_i23(file_output_af, framework_simplified_output, quiet_flag);
	if(!quiet_flag){
		cout << "Query argument in the new created argumentation framework is 1" << endl;
	}

	return 0;
}

int main(int argc, char **argv)
{
	execute(argc, argv);
}