package shuntingyard;
//Anmol Ratol, 30231177
//Creating an algorithm to convert infix expressions to postfix expressions and then evaluate the postfix expressions

import java.util.Stack;

public class Modified_ShuntingYard_Evaluation {
	
	// string of symbols available
	static String acceptables= "[0-9]^*/+-";
	// creating a list of all the operators
	static String[] operators = {"^", "*", "/", "+", "-"};
	
	// converting to postfix
	public static String convertToPostfix(String expression) throws Exception{
		
		// error checking
		if (expression.length() == 0){
			throw new Exception("The input string is empty!");
		}
		
		
		
		// splitting the string into an array
		String[] expArray = expression.split("");
		Stack<String> opStack = new Stack<String>();
		String outputString = "";
		
		for (String elem: expArray){
			
			// if the string elem is an operand, add it to the outputString
			if (isOperand(elem)) { 
				outputString += elem;
			}
			
			// otherwise, place the operator in the stack after moving all other scanned operators
			// of higher precedence into the outputString, if there are any
			else {
				while((!opStack.isEmpty()) && (hasHigherPrecedence(opStack.peek(), elem))){
					outputString += opStack.pop();
				}
				
				opStack.push(elem);
			
			}
			
		}
		
		// shuffle the remaining operators into the output string and return
		while (!opStack.isEmpty()){
			outputString += opStack.pop();
		}
		
		return outputString;
	}
	
	// check the array to see if the string matches anything in the operators list, if not, it is an operand
	private static boolean isOperand(String token){
		
		for (String operator: operators){
			if (token.compareTo(operator) == 0){
				return false;
			}
		}
		
		return true;
	}
	
	// check whether the first operand has higher precedence than the second
	private static boolean hasHigherPrecedence(String op1, String op2){
		return (getPrecedence(op1) >= getPrecedence(op2));
	}
	
	// assigning precedence according to PEMDAS or BEDMAS rules
	private static int getPrecedence(String operator)	{
		
		if (operator.compareTo("^") == 0){
			return 3;
		}
		
		else if ((operator.compareTo("*") == 0) || (operator.compareTo("/") == 0)){
			return 2;
		}
		
		else {
			return 1;
		}
		
	}
	
	// actually evaluating the expression
	public static double evaluatePostfix(String expression){
	
		// split the input string into an array
		String[] expArray = expression.split("");
		Stack<String> evalStack = new Stack<String>();
		double op1 = 0.0;
		double op2 = 0.0;
		double expValue = 0.0;
		
		// cycle through the arrray
		for (String elem: expArray){
			
			// if it is an operand, then push it directly into the stack
			if (isOperand(elem)){
				evalStack.push(elem);
			}
			
			// otherwise, take the operator and the previous two elements from the stack and evaluate it, then push that value onto the stack
			else {
				op2 = Double.parseDouble(evalStack.pop());
				op1 = Double.parseDouble(evalStack.pop());
				
				evalStack.push(String.valueOf(performOperation(op1, op2, elem)));
			}
		}
		
		// return the final value resting on top of the stack
		return Double.parseDouble(evalStack.pop());
		
	}
	
	// converting the inputs to the double value based on the operator
	private static double performOperation(double operand1, double operand2, String operator){
	
		if (operator.compareTo("^") == 0){
			return Math.pow(operand1, operand2);
		}
		
		else if (operator.compareTo("*") == 0) {
			return operand1*operand2;
		}
		
		else if (operator.compareTo("/") == 0){
			return operand1/operand2;
		}
		
		else if (operator.compareTo("+") == 0){
			return operand1+operand2;
		}
		
		else {
			return operand1-operand2;
		}
	}
	
	// copied from template
	public static void main ( String [] args ) throws Exception {
		String expression1 = "2+3*1" ;
		String expression2 = "3*2^4-7" ;
		String expression3 = "3*2^4-a" ;
		String postfix1 = convertToPostfix ( expression1 ) ;
		String postfix2 = convertToPostfix ( expression2 ) ;
		String postfix3 = convertToPostfix ( expression3 ) ;
		System.out.println ( expression1 + "−>Postfix: " + postfix1 + " , Evaluation: "  + evaluatePostfix ( postfix1 ) ) ;
		System.out.println ( expression2 + "−>Postfix: " + postfix2 + " , Evaluation: "  + evaluatePostfix ( postfix2 ) ) ;
	}
	
	
}
