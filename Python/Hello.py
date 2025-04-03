import re
from xml.etree.ElementTree import Element, SubElement, tostring
from xml.dom import minidom

def parse_function_declaration(text):
    # Estrae il nome della funzione
    function_name_match = re.search(r'(\w+)\s*:', text)
    if not function_name_match:
        return None
    function_name = function_name_match.group(1)

    # Estrae la descrizione
    description_match = re.search(r':\s*(.*?)\n', text)
    description = description_match.group(1).strip() if description_match else ""

    # Estrae il tipo di ritorno
    return_type_match = re.search(r'returns\s+(\w+)', text)
    return_type = return_type_match.group(1) if return_type_match else ""

    # Estrae i parametri solo se è presente la parola "Parameters"
    parameters = []
    if "Parameters" in text:
        # Trova la sezione dei parametri (cattura tutto fino a "Autotype" o "returns")
        parameters_section = re.search(r'Parameters\s*((?:\n\s*•\s*.+)+)', text)
        if parameters_section:
            print("Sezione parametri trovata:")  # Debug
            print(parameters_section.group(1))  # Debug

            # Estrae i parametri nel formato "• nome : tipo" (multiriga)
            parameters = re.findall(r'•\s*([^:\n]+?)\s*:\s*([^\n]+)', parameters_section.group(1))
            print("Parametri estratti:", parameters)  # Debug

            # Pulisci i parametri rimuovendo spazi extra
            parameters = [(name.strip(), type_.strip()) for name, type_ in parameters]

    return {
        'name': function_name,
        'description': description,
        'return_type': return_type,
        'parameters': parameters
    }

def create_xml_element(function_info):
    keyword = Element('KeyWord', name=function_info['name'], func="yes")
    overload = SubElement(keyword, 'Overload', retVal=function_info['return_type'], descr=function_info['description'])

    # Aggiungi i parametri solo se presenti
    for param_name, param_type in function_info['parameters']:
        SubElement(overload, 'Param', name=f"{param_name} : {param_type}")

    return keyword

def prettify(elem):
    """Restituisce una stringa XML formattata in modo leggibile."""
    rough_string = tostring(elem, 'utf-8')
    parsed = minidom.parseString(rough_string)
    return parsed.toprettyxml(indent="  ")

def main(input_file, output_file):
    with open(input_file, 'r', encoding='utf-8') as file:  # Apri il file in UTF-8
        content = file.read()

    # Dividi il contenuto in blocchi di dichiarazioni di funzione
    function_blocks = content.split('(Back to top)')

    root = Element('KeyWords')

    for block in function_blocks:
        function_info = parse_function_declaration(block)
        if function_info:
            xml_element = create_xml_element(function_info)
            root.append(xml_element)

    # Scrivi il file XML
    with open(output_file, 'w', encoding='utf-8') as file:  # Scrivi il file in UTF-8
        file.write(prettify(root))

if __name__ == "__main__":
    input_file = 'functionlistnew.txt'  # Sostituisci con il percorso del tuo file di input
    output_file = 'output.xml'  # Sostituisci con il percorso del file di output desiderato
    main(input_file, output_file)