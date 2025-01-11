# #!/usr2/local/julia-1.10.4/bin/julia
include("CommonData.jl")

#suit is first here but not in constructor so they do not overload each other
mutable struct Card
	suit::Char
	value::Int
end

function Card( newValue::Int, newSuit::Char )
	return Card(newSuit, newValue)
end

function suitRank(card::Card)
	if card.suit == 'D'
		return 1
	elseif card.suit == 'C'
		return 2
	elseif card.suit == 'H'
		return 3
	elseif card.suit == 'S'
		return 4
	else
		return -1
	end
end

function getValue(c::Char)
	i = Int(c)
	if i >= Int('2') && i <= Int('9')
		return (parse(Int, c)-1)
	elseif c == 'J'
		return 10
	elseif c == 'Q'
		return 11
	elseif c == 'K'
		return 12
	elseif c == 'A'
		return 13
	else
		return -1
	end
end

function toString(card::Card)
	return FACES[card.value] * card.suit
end
