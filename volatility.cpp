#include "tsh.hpp"
#include "volatility.hpp"

namespace BEV{
	
	namespace v_surface
	{
		/************************************************
		*************** Volatility Surface **************
		*************************************************/
		
		
		/* constructors and destructors */
		
		volatility_surface::volatility_surface(std::vector<double> maturities, std::vector<double> strikes, std::vector< std::vector<double> >  volatilities)
		: m_strikes(strikes), m_maturities(maturities), m_volatilities(volatilities)
		{
			std::cout<<"volatility_surface constructor"<<std::endl;
		}
		
		volatility_surface::volatility_surface(std::vector<double> maturities, std::vector<v_skew::volatility_skew> vs)
		: m_maturities(maturities), m_strikes(vs[0].get_strikes())
		{
			for(size_t i=0; i<vs.size();++i)
			{
				m_volatilities.push_back(vs[i].get_volatilities());
			}
			std::cout<<"volatility_surface constructor"<<std::endl;
		}
		
		volatility_surface::~volatility_surface()
		{
			std::cout<<"volatility_surface destructor"<<std::endl;
		}
		
		/* getters */
		const std::vector<double>& volatility_surface::get_strikes() const
		{
			return m_strikes;
		}
		
		const std::vector<double>& volatility_surface::get_maturities() const
		{
			return m_maturities;
		}
		
		const std::vector<std::vector<double>>& volatility_surface::get_volatilities() const
		{
			return m_volatilities;
		}
		
		double volatility_surface::get_volatility(double strike, double maturity) const
		{
			return get_volatility_from_index(get_pos_strike(strike),get_pos_maturity(maturity));
		}
		
		double volatility_surface::get_volatility_from_index(std::size_t index1, std::size_t index2) const
		{
			return m_volatilities[index1][index2];
		}
		
		size_t volatility_surface::get_pos_strike(double strike) const
		{
			size_t pos=0;
			std::size_t nb = m_strikes.size();
			size_t i = 0;
			while ((i< nb) && (pos<=0))
			{
				if (m_strikes[i]==strike)
				{
					return i;;
				}
				i++;
			}
			std::cout << "V_surface: Element not found in strikes. First element returned" << std::endl;
			return pos;
		}
		
		size_t volatility_surface::get_pos_maturity(double maturity) const
		{
			size_t pos=0;
			std::size_t nb = m_maturities.size();
			size_t i=0;
			while ((i< nb) && (pos<=0))
			{
				if (m_maturities[i]==maturity)
				{
					return i;
				}
				i++;
			}
			std::cout << "V_surface: Element not found in maturities. First element returned" << std::endl;
			return pos;
		}
		
		/* setters */
		void volatility_surface::set_strikes(std::vector< double> strikes)
		{
			m_strikes = strikes;
		}
		
		void volatility_surface::set_maturities(std::vector< double> maturities)
		{
			m_maturities = maturities;
		}
		
		void volatility_surface::set_volatilities(std::vector< std::vector<double> > volatilities)
		{
			m_volatilities = volatilities;
		}
		
	}		
	
	namespace v_skew
	{
		
		/************************************************
		**************** Volatility Skew ****************
		*************************************************/
		
		/* constructors and destructors */
		
		volatility_skew::volatility_skew(double maturity, std::vector<double> strikes, std::vector<double> volatilities)
		: m_strikes(strikes), m_maturity(maturity), m_volatilities(volatilities)
		{
			std::cout<<"volatility_skew constructor"<<std::endl;
		}
		
		volatility_skew::volatility_skew(double maturity, std::vector<double> strikes)
		: m_strikes(strikes), m_maturity(maturity),m_volatilities(strikes.size(),0)
		{
			std::cout<<"volatility_skew constructor"<<std::endl;
		}
		
		volatility_skew::~volatility_skew()
		{
			std::cout<<"volatility_skew destructor"<<std::endl;
		}
		
		/* getters */
		const std::vector<double>& volatility_skew::get_strikes() const
		{
			return m_strikes;
		}
		
		const std::vector<double>& volatility_skew::get_volatilities() const
		{
			return m_volatilities;
		}
		
		double volatility_skew::get_maturity() const
		{
			return m_maturity;
		}
		
		double volatility_skew::get_volatility(size_t index) const
		{
			return m_volatilities[index];
		}

		double volatility_skew::get_volatility(double strike) const
		{
			return m_volatilities[get_pos(strike)];
		}
		
		ptrdiff_t  volatility_skew::get_pos(double strike) const
		{
			ptrdiff_t pos = distance(m_strikes.begin(), find(m_strikes.begin(), m_strikes.end(), strike));
			if(pos >= m_strikes.size())
			{
				std::cout<< "pos out of bound"<<std::endl;
			}
			return pos;
		}
		
		/* setters */
		void volatility_skew::set_volatilities(std::vector<double> volatilities)
		{
			m_volatilities = volatilities;
		}
		void volatility_skew::set_strikes(std::vector< double> strikes)
		{
			m_strikes = strikes;
		}
		
		void volatility_skew::set_maturity(double maturity)
		{
			m_maturity = maturity;
		}
				
	}
	
	
}