require "../number_generator.rb"
require "../number_util.rb"

class Generator

def initialize test_file_name

end

def init_generator
  @gen = NumberGenerator.new
  @util = NumberUtil.new
  @path_to_tests_folder = "../../../tests/gen"
end
 
def write_metadata
  File.open(@test_file_name, 'w') {|f| 
   f.puts("Title: #{@test_title}#")
   f.puts("Operands: #{@no_of_operands}#")
   f.puts("Type of operands: #{@type_of_operands}#")
   f.puts("Type of result: #{@type_of_result}#")
   }
end
 
def write_test test_hash
 File.open(@test_file_name, 'a') {|f| 
   if (@no_of_operands==2)
    f.puts("##{test_hash["test_no"]} #{test_hash["first_operand"]} #{test_hash["second_operand"]} #{test_hash["result"]}")
   else
    f.puts("##{test_hash["test_no"]} #{test_hash["first_operand"]} #{test_hash["result"]}")
   end
   }
end
 

 
end
